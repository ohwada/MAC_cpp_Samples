#pragma once
/**
 *  http_client.h
 * 2022-06-01 K.OHWADA
 */

// Example HTTP client. Connect to `s_url`, send request, wait for a response
// original : https://github.com/cesanta/mongoose/blob/master/examples/http-client/main.c


#include <string.h>
#include "mongoose.h"


// prototype
void http_client(char *url, bool is_verbose);
void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
void cb_default(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
void http_post_json_client(char *url, char* post_data, bool is_verbose);
void http_post_form_client(char *url, char* post_data, bool is_verbose);  


// prepare a large enough buffer
const size_t RES_SIZE = 10240;  // 10KB
char response[RES_SIZE];

// Connect timeout in milliseconds
static const uint64_t TIMEOUT_MS = 1500;  

// global
// web site 
char *s_url = "";
// POST data
char *s_post_data = NULL;      

bool g_is_verbose = false;
bool g_is_post_form = false;
bool g_is_post_json = false;


/**
 *  http_client
 */
void http_client(char *url, bool is_verbose) 
{

    const char NUL = '\0';

    memset(response, NUL, RES_SIZE);

// Use URL provided in the command line
    s_url = url;

   g_is_verbose = is_verbose;

  const char *log_level = getenv("LOG_LEVEL");  // Allow user to set log level
  if (log_level == NULL) log_level = "4";       // Default is verbose

  struct mg_mgr mgr;              // Event manager
  bool done = false;              // Event handler flips it to true
  mg_mgr_init(&mgr);              // Initialise event manager
 // Create client connection
  mg_http_connect(&mgr, url, cb, &done);     
  while (!done) mg_mgr_poll(&mgr, 50);      // Event manager loops until 'done'
  mg_mgr_free(&mgr);                        // Free resources
}


/**
 *  http_post_form_client
 */
void http_post_form_client(char *url, char* post_data, bool is_verbose) 
{
    s_post_data = post_data;
    g_is_post_form = true;

    http_client(url, is_verbose); 
}


/**
 *  http_post_json_client
 */
void http_post_json_client(char *url, char* post_data, bool is_verbose) 
{
   s_post_data = post_data;
    g_is_post_json = true;

    http_client(url, is_verbose); 
}


/**
 *  cb_default
 */
// Print HTTP response and signal that we're done
void cb_default(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    char* FORMAT_GET = 
    (char *)"GET %s HTTP/1.0\r\n"
    "Host: %.*s\r\n"
    "Accept: */* \r\n"
    "Connection: close\r\n\r\n";

    char* FORMAT_POST_FORM = 
    (char *)"POST %s HTTP/1.0\r\n"
    "Host: %.*s\r\n"
    "Accept: */* \r\n"
    "Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n"
    "Content-Length: %d\r\n"
    "\r\n";

    char* FORMAT_POST_JSON = 
    (char *)"POST %s HTTP/1.0\r\n"
    "Host: %.*s\r\n"
    "Accept: */* \r\n"
    "Content-Type: application/json; charset=utf-8\r\n"
    "Content-Length: %d\r\n"
    "\r\n";

    const char NUL = '\0';

    char *ca_pem = (char *)"cert/ca.pem";

  if (ev == MG_EV_OPEN) {
    // Connection created. Store connect expiration time in c->label
    printf("\n connect: %s \n", s_url);
    *(uint64_t *) c->label = mg_millis() + TIMEOUT_MS;
  } else if (ev == MG_EV_POLL) {
    if (mg_millis() > *(uint64_t *) c->label &&
        (c->is_connecting || c->is_resolving)) {
      mg_error(c, "Connect timeout");
    }
  } else if (ev == MG_EV_CONNECT) {
    // Connected to server. Extract host name from URL
    struct mg_str host = mg_url_host(s_url);

    // If s_url is https://, tell client connection to use TLS
    if (mg_url_is_ssl(s_url)) {
      struct mg_tls_opts opts = {.ca = ca_pem, .srvname = host};
      mg_tls_init(c, &opts);
        printf("ssl: %s \n", ca_pem);
    }

  
    // Send request
    char* path = (char *)mg_url_uri(s_url);
    int content_length = s_post_data ? strlen(s_post_data) : 0;
    if(g_is_post_form){
            mg_printf(c, FORMAT_POST_FORM, 
            path, (int)host.len, host.ptr, content_length);
    }else if(g_is_post_json){
            mg_printf(c, FORMAT_POST_JSON, 
            path, (int)host.len, host.ptr, content_length);
    } else {
            mg_printf(c, FORMAT_GET, 
            path, (int)host.len, host.ptr);
    }
        mg_send(c, s_post_data, content_length);
  } else if (ev == MG_EV_HTTP_MSG) {
    // Response is received. Print it
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    int msg_len = (int)hm->message.len;
    if(g_is_verbose) {
        printf("%.*s", msg_len, hm->message.ptr);
    }
    char buf[msg_len + 1];
    strncpy( (char *)buf, hm->message.ptr, msg_len);
    buf[msg_len] = NUL;
    strcat( (char *)response, (char *)buf);

// Tell mongoose to close this connection
    c->is_closing = 1; 
// Tell event loop to stop
            *(bool *) fn_data = true;  
  } else if (ev == MG_EV_ERROR) {
// Error, tell event loop to stop
    *(bool *) fn_data = true;    }
}


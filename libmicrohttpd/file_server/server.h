#pragma once
/**
 * server.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/minimal_example.c

#include <stdbool.h>
#include "platform.h"
#include <microhttpd.h>

#define PAGE "<html><head><title>libmicrohttpd demo</title></head><body><h1>libmicrohttpd demo</h1></body></html>"

// prototype
bool run_server(int port);
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr);
int response_text_persistent (
    struct MHD_Connection *connection, 
    char *text, char* mime);
int response_text_copy (
    struct MHD_Connection *connection, 
    char *text, char* mime);


/**
 * run_server
 */
bool run_server(int port)
{
  struct MHD_Daemon *d;

  d = MHD_start_daemon (
        MHD_USE_SELECT_INTERNALLY | 
        MHD_USE_DEBUG,
                        port,
                        NULL, NULL, (void *)&ahc_echo, PAGE,
			MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 120,
			MHD_OPTION_END);

  if (d == NULL) {
    return false;
}

printf("listen port : %d \n", port);

  printf("enter return key to qiut \n");

(void) getc (stdin);

  MHD_stop_daemon (d);

  return true;
}


/**
 * response_text
 */
int response_text_persistent (
    struct MHD_Connection *connection, 
    char *text, char* mime)
{
    if( (text == NULL)||( strlen(text)==0) ){
        return MHD_NO;
    }

  struct MHD_Response *response;
  int ret;

  response = MHD_create_response_from_buffer (strlen (text),
					      (void *) text,
					      MHD_RESPMEM_PERSISTENT);

    if (response == NULL) {
        return MHD_NO;
    }

    MHD_add_response_header (response, "Content-Type", mime);

  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);

  MHD_destroy_response (response);

  return ret;
}


/**
 * response_text
 */
int response_text_copy (
    struct MHD_Connection *connection, 
    char *text, char* mime)
{
    if( (text == NULL)||( strlen(text)==0) ){
        return MHD_NO;
    }

  struct MHD_Response *response;
  int ret;

  response = MHD_create_response_from_buffer (strlen (text),
					      (void *) text,
					      MHD_RESPMEM_MUST_COPY);

    if (response == NULL) {
        return MHD_NO;
    }

    MHD_add_response_header (response, "Content-Type", mime);

  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);

  MHD_destroy_response (response);

  return ret;
}

#pragma once
/**
 * request_post_builder.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// prototype
void build_http_post_form_request(char *host, char *path,  char* post_data, char *request);
void build_http_post_json_request(char *host, char *path,  char* post_data, char *request);
void build_http_post_form_headers(char *host, char *path,  int length, char *headers);
void build_http_post_json_headers(char *host, char *path,  int length, char *headers);
void build_http_post_headers(char *host, char *path, char* mime, int length, char *headers);


/** 
 *  build_http_post_form_request
 */
void build_http_post_form_request(char *host, char *path,  char* post_data, char *request)
{

    const char CRLF[] = "\r\n"; 

    const size_t BUFSIZE = 1024;
    char headers[BUFSIZE];

    int length = strlen(post_data);

    build_http_post_form_headers(host, path,  length, (char *)headers);

    strcpy(request,  (char *)headers);
    strcat(request, (char *)CRLF);
    strcat(request,  (char *)post_data);
    strcat(request,  (char *)CRLF);

}


/** 
 *  build_http_post_json_request
 */
void build_http_post_json_request(char *host, char *path,  char* post_data, char *request)
{

    const char CRLF[] = "\r\n"; 

    const size_t BUFSIZE = 1024;
    char headers[BUFSIZE];

    int length = strlen(post_data);

    build_http_post_json_headers(host, path,  length, (char *)headers);

    strcpy(request,  (char *)headers);
    strcat(request, (char *)CRLF);
    strcat(request,  (char *)post_data);
    strcat(request,  (char *)CRLF);

}

/** 
 *  build_http_post_form_headers
 */
void build_http_post_form_headers(char *host, char *path,  int length, char *headers)
{

    char* mime = 
"application/x-www-form-urlencoded; charset=utf-8";

    build_http_post_headers(host, path, mime, length, headers);
}


/** 
 *  build_http_post_json_headers
 */
void build_http_post_json_headers(char *host, char *path, int length, char *headers)
{

    char* mime = "application/json; charset=utf-8";

    build_http_post_headers(host, path, mime, length, headers);
}

/** 
 *  build_http_post_headers
 */
void build_http_post_headers(char *host, char *path, char* mime, int length, char *headers)
{

 const char HEADER_ACCEPT_ALL[] = "Accept: */* \r\n";

// const char HEADER_CLOSE[] = "Connection: close\r\n\r\n";

// Do not put spaces after HTTP/1.1 
 const char FORMAT_REQUEST[] = "POST %s HTTP/1.1\r\n";

 const char FORMAT_HOST[] = "Host: %s\r\n";

 const char FORMAT_CONTENT_TYPE[] = "Content-Type: %s\r\n";

 const char FORMAT_CONTENT_LENGTH[] = "Content-Length: %d\r\n";

    const size_t BUFSIZE = 128;
    char hdr_request[BUFSIZE];
    char hdr_host[BUFSIZE];
    char hdr_content_type[BUFSIZE];
    char hdr_content_length[BUFSIZE];

  snprintf( (char *)hdr_request, BUFSIZE, (char *)FORMAT_REQUEST, (char *)path);

  snprintf( (char *)hdr_host, BUFSIZE, (char *)FORMAT_HOST, (char *)host ); 

snprintf( (char *)hdr_content_type, BUFSIZE, (char *)FORMAT_CONTENT_TYPE, (char *)mime ); 

snprintf( (char *)hdr_content_length, BUFSIZE, (char *)FORMAT_CONTENT_LENGTH, length );

  strcpy(headers, hdr_request);

  strcat(headers, HEADER_ACCEPT_ALL);

  strcat(headers,  hdr_host); 

  strcat(headers,  hdr_content_type); 

  strcat(headers,  hdr_content_length); 

}



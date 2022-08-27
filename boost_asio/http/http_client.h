#pragma once
/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// function for HTTP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// constant
const uint16_t PORT_HTTP = 80;

const char *ROOT_PATH = "/";


// prototype
void build_http_root_path_request(char *host, char *request);
void build_http_request(char *host, char *path, char *request);


/** 
 *  build_http_root_path_request
 */
void build_http_root_path_request(char *host, char *request)
{
    build_http_request( host, (char *)ROOT_PATH, request);
}


/** 
 *  build_http_request
 */
void build_http_request(char *host, char *path, char *request)
{

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

  snprintf(buf, BUFSIZE, "GET %s HTTP/1.1\r\n", (char *)path);
  strcpy(request, buf);

  strcat(request, "Accept: */* \r\n");

  snprintf(buf, BUFSIZE, "Host: %s\r\n", (char *)host ); 
  strcat(request, buf); 

   strcat(request, "Connection: close\r\n\r\n"); 
}


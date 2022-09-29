#pragma once
/**
 * network sample
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

 const char HEADER_ACCEPT_ALL[] = "Accept: */* \r\n";
const char HEADER_CLOSE[] = "Connection: close\r\n\r\n";

// Do not put spaces after HTTP/1.1　
 const char FORMAT_GET[] = "GET %s HTTP/1.1\r\n";

 const char FORMAT_HOST[] = "Host: %s\r\n";

    const size_t BUFSIZE = 100;
    char hdr_get[BUFSIZE];
    char hdr_host[BUFSIZE];

  snprintf(hdr_get, BUFSIZE, FORMAT_GET, (char *)path);

  snprintf( hdr_host, BUFSIZE, FORMAT_HOST, (char *)host ); 

  strcpy(request, hdr_get);

  strcat(request, HEADER_ACCEPT_ALL);

  strcat(request,  hdr_host); 

   strcat(request, HEADER_CLOSE); 
}


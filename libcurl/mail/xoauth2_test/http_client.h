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
bool http_client(char* host, int port, char* request, char* response, int max, char* error, bool is_verbose );
void build_http_root_path_request(char *host, char *request);
void build_http_request(char *host, char *path, char *request);
bool split_header_body(char* text, char* header, char* body);


/** 
 *   http_client
 */
bool http_client(char* host, int port, char* request, char* response, int max, char* error, bool is_verbose)
{

    const size_t CHUNK_SIZE = 128;

    const int READ_TIMEOUT = 10; // 10 sec

  // create socket
    int sockfd ;
    sockfd  = tcp_socket( error );

    if( sockfd  < 0){
            return false;
    }

  // connect to server
    bool ret1 = tcp_connect_hostname( sockfd, (char *)host,  port , error );

    if(!ret1){
        close( sockfd );
        return false;
    }


    printf("connect to : %s : %d \n", host, port );

// send request
    bool ret2 = tcp_write( sockfd, request, error);

    if(!ret2){
        close( sockfd );
        return false;
    }

    set_tcp_read_timeout(sockfd, READ_TIMEOUT);

// recieve response
bool ret3 = tcp_block_read(sockfd, response, CHUNK_SIZE, max, is_verbose, error);
   
    if(!ret3){
        close(sockfd );
        return false;
    }


// close
    close(sockfd );

    return true;
}


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


/*
 *  split_header_body
*/
bool split_header_body(char* text, char* header, char* body)
{

    const char NUL = '\0';

    const char* delim = "\r\n\r\n"; 

    char buf[strlen(text)+1];

    strcpy(buf, text);

    char* p = strstr(buf, delim);

    if(p==NULL){
        return false;
    }

    *p = NUL;

   strcpy( header, buf);
    strcpy( body, &p[4]);

    return true;
}


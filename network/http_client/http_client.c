/**
 * http_client.c
 * 2022-06-01 K.OHWADA
 */

// simle HTTP Client
// get web page from HTTP server

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/02/24/133529

// reference : http://x68000.q-e-d.net/~68user/net/c-http-1.html


#include <stdio.h>
#include <stdlib.h>
#include "tcp_client.h"
#include "http_client.h"
#include "request_builder.h"
#include "main_proc.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    char* host = "example.com";

    int port = PORT_HTTP;


    bool is_verbose = false;


    if(argc == 4) {
      	host = argv[1];
      	port = atoi( argv[2] );
        is_verbose = (bool)atoi( argv[3] );
    } else if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] \n",  argv[0] );
    }

    printf("host: %s \n",  host );
    printf("port: %d \n",  port );
    printf(" is_verbose: %d \n",   is_verbose );

// TODO:
// variable length buffer
// Note:
// Google response size is 54KB
    const size_t BUFSIZE = 102400; // 100KB
    char response[BUFSIZE];


    const size_t REQ_SIZE = 1024; // 1KB
    char request[REQ_SIZE];
    char error[REQ_SIZE];

    const char NUL = '\0';

// Note
// for Google: received 49 times
    const int LOOP = 60;

// clear buffer
    memset(response, NUL, BUFSIZE);

// create GET request 
    build_http_root_path_request( (char *)host, (char *)request);

    printf("request \n");
    printf("%s \n", (char *)request );
// request size: 73
    printf("request size: %zu \n", strlen(request) );

bool ret1 = http_client(host, port, (char *)request, (char *) response, LOOP, (char *)error, is_verbose );
    if(!ret1){
            return EXIT_FAILURE;
    }

    proc_response1( (char *)response);

    return EXIT_SUCCESS;
}


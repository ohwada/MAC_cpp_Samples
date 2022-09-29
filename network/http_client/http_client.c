/**
 * network sample
 * 2020-07-01 K.OHWADA
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

/**
 * main
 */
int main(int argc, char *argv[])
{

    char* host = "example.com";

    int port = PORT_HTTP;

    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] \n",  argv[0] );
    }

    printf("host: %s \n",  host );
    printf("port: %d \n",  port );

 const size_t BUFSIZE = 1024;
    char request[BUFSIZE];
 const size_t ERR_SIZE = 100;
    char error[ERR_SIZE];


// create GET request 
    build_http_root_path_request( (char *)host, (char *)request);

    printf("request \n");
    printf("%s \n", (char *)request );


  // create socket
    int sockfd ;
    sockfd  = tcp_socket( (char *)error );

    if( sockfd  < 0){
            fprintf(stderr, "tcp_socket: %s \n", error );
            return EXIT_FAILURE;
    }

  // connect to server
    bool ret1 = tcp_connect_hostname( sockfd, (char *)host,  port , (char *)error );

    if(!ret1){
       fprintf( stderr, "tcp_connect_hostname: %s : %d : %s \n", host,  port, error);
        goto label_error;
    }


  printf("connect to : %s : %d \n", host, port );




// send request
    bool ret2 = tcp_write( sockfd, (char *)request, (char *)error);

    if(!ret2){
        fprintf(stderr, "tcp_write: %s \n", error);
        goto label_error;
    }

// recieve response
 printf("response \n");
    bool ret3 = print_tcp_read( sockfd, (char *)error );

    if(!ret3){
        fprintf(stderr, "tcp_read: %s \n", error);
        goto label_error;
    }


// close
    close(sockfd );

    fprintf(stderr, "sucessful \n");

    return EXIT_SUCCESS;


// --- error ---
label_error:

    if(sockfd){
        close( sockfd );
    }

    fprintf(stderr, "failed \n");

    return EXIT_FAILURE;
}


// Conntect to: example.com : 80 
// <title>Example Domain</title>


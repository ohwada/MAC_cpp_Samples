/**
 * http_hello_server.h
 * 2022-06-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.geekpage.jp/programming/linux-network/http-server.php


#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include "tcp_server.h"
#include "response_sender.h"


void on_accept(sockfd_client)
{
    const size_t BUFSIZE = 1024;
    char recv_buf[BUFSIZE];
    char error[BUFSIZE];

// recv packet
    int size_read = tcp_read2( sockfd_client, (char *)recv_buf, BUFSIZE, (char *)error );
  
    if( size_read == 0 ) {
                printf("maybe client socket closed \n");
                return;
    } else if (size_read < 0) {
            fprintf(stderr, "tcp_read: %s \n", error );
            return;
    }

   printf("\n request \n");
    printf("%s", recv_buf);

    char *text = "Hello World";
    char *mime = "text/plain";

    send_response_text(sockfd_client, text, mime);

}


/**
 * main
 */
int main(int argc, char *argv[])
{

    int port = 8080;

    if(argc == 2){
      	port = atoi( argv[2] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

    printf("port: %d \n",  port );

    bool ret = run_server(port);
    if(!ret){
            return EXIT_FAILURE;
    }

    printf("successful \n");

    return EXIT_SUCCESS;
}

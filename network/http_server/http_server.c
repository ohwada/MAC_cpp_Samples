/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.geekpage.jp/programming/linux-network/http-server.php


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "http_server.h"
#include "tcp_server.h"
#include "file_util.h"


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

    const size_t BUFSIZE = 1024;
    char response[BUFSIZE];
    char recv_buf[BUFSIZE];

    const size_t ERR_SIZE = 512;
    char error[ERR_SIZE];

    bool ret = get_index_html_response( (char *)response, (char*)error);
    if( !ret ) {
        printf("%s \n", error);
        return EXIT_FAILURE;
    }

    printf("%s \n", response);

    const int backlog = 5;

    int sockfd_listen;

    int sockfd_client;


// create socket
    sockfd_listen =  tcp_socket_listen_port( port, backlog, (char *)error );

    if (sockfd_listen < 0) {
        fprintf(stderr, "socket: %s \n", error );
        return EXIT_FAILURE;
    }

    printf("listen port: %d \n", port );


    bool is_verboce = true;

 while (1) 
{

    sockfd_client = tcp_accept( sockfd_listen, (char *)error, is_verboce);

   if (sockfd_client < 0) {
        fprintf(stderr, "accept: %s \n", error );
	   break;
   }


// recv packet
    int size_read = tcp_read( sockfd_client, (char *)recv_buf, BUFSIZE, (char *)error );
  
    if( size_read == 0 ) {
                // close
                printf("maybe client socket closed \n");
	            close(sockfd_client); 
                break;
    } else if (size_read < 0) {
        // error
        fprintf(stderr, "tcp_read: %s \n", error );
    }

    printf("%s", recv_buf);

// Normally, YOU should parse the request from the client.

// send fixed prepared response
bool ret1 = tcp_write( sockfd_client, (char *)response, (char *)error );

    if(!ret1) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

     close(sockfd_client);

 } // while

    if(sockfd_client){
        close(sockfd_client);
    }

    close(sockfd_listen);

    printf("successful \n");

    return EXIT_SUCCESS;


// --- error ---
// label_error:


    if(sockfd_listen){
        close(sockfd_listen);
    }

    if(sockfd_client){
        close(sockfd_client);
    }

    printf("failed \n");

    return EXIT_FAILURE;
}

#pragma once
/**
 * http_server.h
 * 2022-06-01 K.OHWADA
 */

// function for HTTP Server


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcp_server.h"


// prototype
bool run_server( unsigned short port);
void on_accept(int sockfd_client);


/**
 * run_server
 */
bool run_server( unsigned short port)
{

    const int BACKLOG = 5;

    const int READ_TIMEOUT = 10; // 10 sec 

    const size_t ERR_SIZE = 512;
    char error[ERR_SIZE];

    int sockfd_listen;

    int sockfd_client;

// create socket
    sockfd_listen =  tcp_socket_listen_port( port, BACKLOG, (char *)error );

    if (sockfd_listen < 0) {
        fprintf(stderr, "socket: %s \n", error );
        return false;
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

    set_tcp_read_timeout(sockfd_client, READ_TIMEOUT);

    on_accept(sockfd_client);

     close(sockfd_client);

 } // while

    if(sockfd_client){
        close(sockfd_client);
    }

    close(sockfd_listen);

    return true;
}


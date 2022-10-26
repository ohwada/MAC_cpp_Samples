#pragma once
/**
 * http_client.h
 * 2022-06-01 K.OHWADA
 */

// function for HTTP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// constant
const uint16_t PORT_HTTP = 80;


// prototype
bool http_client(char* host, int port, char* request, char* response, int loop, char* error, bool is_verbose );


/** 
 *   http_client
 */
bool http_client(char* host, int port, char* request, char* response, int loop, char* error, bool is_verbose)
{

    const size_t BLOCK_SIZE = 1024;

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
bool ret3 = tcp_block_read(sockfd, response, BLOCK_SIZE, loop, is_verbose, error);
   
    if(!ret3){
        close(sockfd );
        return false;
    }


// close
    close(sockfd );

    return true;
}


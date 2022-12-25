/**
 * ws_client.c
 * 2022-10-01 K.OHWADA
 */

//  Websocket  Client in C
// handshake send text send ping snd close

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_client.h"
#include "ws_client.h"
#include "port.h"


/** 
 *   ws_client
 */
bool ws_client(char* host,  unsigned short port, char* path, char *text, bool is_ping, bool is_verbose)
{
    const size_t ERR_SIZE = 100;
    char error[ERR_SIZE];


    const int READ_TIMEOUT = 10; // 10 sec

    const int SLEEP = 5; // 5 sec

    int sockfd = tcp_connect_server(host, port, READ_TIMEOUT, (char *)error );

    if( sockfd  < 0){
            printf("tcp_connect_server: %s \n", error);
            return false;
    }

    printf("connect to : %s : %d \n", host, port );

    bool ret1 = ws_handshake(sockfd, host, path, is_verbose);
   
 if(!ret1){
        close( sockfd );
        return false;
    }


    printf("send text: %s \n", text);
    bool ret2 = send_text(sockfd, text);

    if(!ret2){
        close(sockfd );
        return false;
    }

// send ping
    if (is_ping) {
        sleep(SLEEP);

        printf("\n send ping \n");
        bool ret3 = send_ping(sockfd);

        if(!ret3){
            close(sockfd );
            return false;
        }

    }


    sleep(SLEEP);

// closing
    bool ret4 = send_close(sockfd, CLOSE_NORMAL, NULL);

    if(!ret4){
        close(sockfd );
        return false;
    }

    sleep(SLEEP);

    close(sockfd );

    printf("\n close \n");

    return true;
}


/**
 * main
 */
int main(int argc, char *argv[])
{

    char* host =  (char *)"localhost";

     unsigned short port = PORT;

    char* path = (char *)ROOT_PATH;

    char *text = "Hello World";

    bool is_ping = true;
    bool is_verbose = false;

    if(argc == 5) {
      	host = argv[1];
      	port = atoi( argv[2] );
      	path = argv[3];
        text = argv[4];
    } else if(argc == 4) {
        host = argv[1];
      	port = atoi( argv[2] );
        path = argv[3];
    } else if(argc == 3) {
        host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	text = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] [path] [text]  \n",  argv[0] );
    }

    printf("host: %s \n",  host );
    printf("port: %d \n",  port );
    printf("path: %s \n",  path );
    printf("text: %s \n",  text );
    printf(" is_verbose: %d \n",   is_verbose );

    bool ret1 = ws_client(host, port, path, text, is_ping, is_verbose );
    if(!ret1){
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// connect to : localhost : 8080 
// response 
// HTTP/1.1 101 Switching Protocols
// Upgrade: websocket
// Connection: upgrade
// Sec-WebSocket-Accept: sWz+iaFYxHOhdIYWB3i9KEKJjAQ=
// Server: Boost.Beast/330 websocket-server-sync


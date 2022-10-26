/**
 * http_cookie_server.c
 * 2022-06-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.geekpage.jp/programming/linux-network/http-server.php


#include <stdio.h>
#include <stdlib.h>
#include "http_cookie_server.h"
#include "tcp_server.h"
#include "request_parser.h"
#include "response_sender.h"


void send_response_cokie(int sockfd_client, int visits)
{

const size_t BUFSIZE = 1024;
    char response[BUFSIZE];
    char msg[BUFSIZE];
 char error[BUFSIZE];

    char *mime = "text/html";

          build_msg_visits( visits, (char *)msg);
            build_cookie_response( (char *)msg, mime, visits, (char *)response);

   printf("\n response \n");
    printf("%s \n", response);

// send fixed prepared response
bool ret3 = tcp_write1( sockfd_client, (char *)response, (char *)error );

    if(!ret3) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }
}


/**
 * on_accept
 */
void on_accept(sockfd_client)
{


    const char SLASH[] = "/";

    const size_t BUFSIZE = 1024;
    char recv_buf[BUFSIZE];
    char path[BUFSIZE];
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

bool is_root = false;

    bool ret1 = parse_path( (char *)recv_buf,  (char *)path);
    if(ret1){
        printf("path: %s \n", path);
        if( strcmp(path, SLASH) == 0) {
            is_root = true;
        }
    }

    int visits = 0;

    bool ret2 = parse_cookie_visits( (char *)recv_buf,  &visits);
    if(ret2){
        printf("visits: %d \n", visits);
        visits ++;
    } else {
        visits = 1;
    }

    if(is_root) {
        send_response_cokie(sockfd_client, visits);
    } else {
        char* file = "data/index.html";
        send_response_file(sockfd_client, file);        ;
    }

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

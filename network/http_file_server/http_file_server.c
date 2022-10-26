/**
 * http_file_server.c
 * 2022-06-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.geekpage.jp/programming/linux-network/http-server.php


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include "http_server.h"
#include "tcp_server.h"
#include "http_file_server.h"
#include "request_parser.h"
#include "response_sender.h"
#include "not_found_builder.h"



/**
 * send_response_not_found
 */
void send_response_not_found(int sockfd_client, char* path)
{
    const size_t BUFSIZE = 1024; // 1KB
    char header[BUFSIZE];
    char msg[BUFSIZE];
    char error[BUFSIZE];

    build_msg_not_found( path, (char *)msg);

     int length = (int)strlen(msg);
    char *mime = "text/html";
    bool is_crlf = true;  
  
    build_response_header_not_found(length, mime, is_crlf, (char *)header);

    bool ret1 = tcp_write1( sockfd_client, (char *)header, (char *)error );
    if(!ret1) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

    bool ret2 = tcp_write1( sockfd_client, (char *)msg, (char *)error );
    if(!ret2) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

}


/**
 * on_accept
 */
void on_accept(int sockfd_client)
{

    const size_t BUFSIZE = 1024;
    char recv_buf[BUFSIZE];
    char path[BUFSIZE];
   char file[BUFSIZE];
    char error[BUFSIZE];

// recv packet
    int size_read = tcp_read2( sockfd_client, (char *)recv_buf, BUFSIZE, (char *)error );
  
    if( size_read == 0 ) {
            printf("maybe client socket closed \n");
            return;
    } else if (size_read < 0) {
            fprintf(stderr, "tcp_read: %s \n", error );
char* file="www/index.html";
send_response_file(sockfd_client, (char *)file);
            return;
    }

   printf("\n request \n");
    printf("%s", recv_buf);

// Normally, YOU should parse the request from the client.

    bool ret2 = parse_path( (char* )recv_buf,  (char * )path);
    if(!ret2){
        printf("cannot parse_request \n");
char* file="www/index.html";
send_response_file(sockfd_client, (char *)file);
        return;
    }

       printf("path: %s \n", path);

        get_file( (char *)path, (char *)file);
       printf("file: %s \n", file);
   
    if( file_exists(file) ){
        send_response_file(sockfd_client, file);
    } else {
        send_response_not_found(sockfd_client, (char *)path);
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

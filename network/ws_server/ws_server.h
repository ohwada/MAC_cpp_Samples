#pragma once
/**
 * ws_server.h
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include "http_response_sender.h"
#include "ws_request_parser.h"
#include "ws_response_builder.h"
#include "ws_server_frame_builder.h"
#include "ws_frame_parser.h"
#include "ws_frame_sender.h"
#include "ws_frame_common.h"


// prototype
bool ws_handshake(int sockfd_client);
void proc_text(int sockfd, char *read_data, size_t data_suze );
void proc_close(int sockfd,  char *read_data, size_t data_suze );
void proc_ping(int sockfd, char *read_data, size_t data_suze );


/**
 * ws_handshake
 */
bool ws_handshake(int sockfd_client)
{
// If the request have "Sec-WebSocket-Key" header, 
// send back the handshake response.
//  as WebSocket opening handshake
// If the request doesn't have "Sec-WebSocket-Key" header, 
// send back index.html, 
// considered as access from a Web Browser

    const size_t BUFSIZE = 1024;
    char response[BUFSIZE];
    char request[BUFSIZE];

    const size_t ERR_SIZE = 100;
    char error[ERR_SIZE];

    const size_t KEY_SIZE = 100;
    char sec_key[KEY_SIZE];
    char accept_key[KEY_SIZE];

    memset(request, NUL, BUFSIZE);

// recv request
    bool ret1 = tcp_read_str( sockfd_client, (char *)request, (char *)error );
  
    if (!ret1) {
            fprintf(stderr, "tcp_read: %s \n", error );
            return false;
    }

   printf("\n request \n");
    printf("%s \n", request);

    bool ret2 = parse_seckey( (char *)request, (char *)sec_key);
    if (!ret2){
        printf("no sec key \n");
        char *file = "www/index.html";
        send_response_file(sockfd_client, file);
        return false;
    }

    printf("sec_key: %s \n", sec_key);

    gen_accept_key( (char *)sec_key, (char *)accept_key);

    printf("accept_key: %s \n", accept_key);

    ws_build_response( (char *)accept_key, (char *)response);

    printf("\n response \n");
    printf("%s \n", response);


// send response
bool ret3 = tcp_write_str( sockfd_client, (char *)response, (char *)error );
    if(!ret3) {
        fprintf(stderr, "tcp_write: %s \n", error );
        return false;
    }

    return true;
}


/**
 * proc_text
 */
void proc_text(int sockfd, char *read_data, size_t read_data_size )
{
    const size_t DATA_SIZE = 200;
    char write_data[DATA_SIZE];
    char text[DATA_SIZE];

    parse_text( (char *)read_data, read_data_size, (char *)text);

    memset(write_data, NUL, DATA_SIZE);

    size_t  write_data_size;

    build_server_text( (char *)text, (char *)write_data, &write_data_size);

    printf("send text: %s \n", text);

    frame_write(sockfd, (char *)write_data, write_data_size);

}


/**
 * proc_close
 */
void proc_close(int sockfd,  char *read_data, size_t read_data_size )
{
    const char NUL = '\0';

    const size_t DATA_SIZE = 100;
    char write_data[DATA_SIZE];
    char reason[DATA_SIZE];

    int recv_code = 0;
    int send_code = 0;

    bool ret = parse_close(read_data, read_data_size, &recv_code, (char *)reason);


    if(ret){
        send_code = recv_code;
      } else {
        send_code = CLOSE_NORMAL;
     }


    memset(write_data, NUL, DATA_SIZE);

    size_t  write_data_size;

    build_server_close( send_code , (char *)reason, (char *)write_data, &write_data_size);

    printf("send close: %d : %s \n", send_code, reason);

    frame_write(sockfd, (char *)write_data, write_data_size);

}


/**
 * proc_ping
 */
void proc_ping(int sockfd, char *read_data, size_t read_data_size )
{    
    const char NUL = '\0';

    const size_t DATA_SIZE = 100;
    char write_data[DATA_SIZE];

    memset(write_data, NUL, DATA_SIZE);

    size_t  write_data_size;

    build_server_pong( (char *)write_data, &write_data_size);

    printf("send Pong \n");
    frame_write(sockfd, (char *)write_data, write_data_size);

}


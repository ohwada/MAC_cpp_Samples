#pragma once
/**
 * ws_client.h
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tcp_client.h"
#include "ws_request_builder.h"
#include "ws_client_frame_builder.h"
#include "ws_frame_parser.h"
#include "ws_frame_sender.h"
#include "ws_frame_common.h"

// prototype
bool ws_handshake(int sockfd, char* host, char* path,  bool is_verbose);
bool send_text(int sockfd, char *text);
bool send_close(int sockfd, int code, char *reason);
bool send_ping(int sockfd);
bool frame_read(int sockfd);


/** 
 *   ws_handshake
 */
bool ws_handshake(int sockfd, char* host, char* path,  bool is_verbose)
{
    const char NUL = '\0';

    const size_t BUFSIZE = 1024; 
    char request[BUFSIZE];
    char response[BUFSIZE];

    const size_t ERR_SIZE = 100; 
    char error[ERR_SIZE];

    const size_t KEYSIZE = 10;
    char key[2*KEYSIZE];

    const size_t BLOCK_SIZE = 1024;
    const int LOOP = 3;

// opening
    gen_ws_key((char *)key,  KEYSIZE);
    printf("key: %s \n", key);

    build_ws_request( (char *)host, (char *)path, (char *)key, (char *)request);

    printf("\n request \n");
    printf("%s \n", request );
// send request
    bool ret2 = tcp_write_str( sockfd, request, error);

    if(!ret2){
        printf("error: %s \n", error);
        close( sockfd );
        return false;
    }


// recieve response
    memset(response, NUL, BUFSIZE);

    bool ret3 = tcp_block_read(sockfd, response, BLOCK_SIZE, LOOP, is_verbose, error);
   
    if(!ret3){
        printf("error: %s \n", error);
        close(sockfd );
        return false;
    }

    printf("response \n");
    printf("%s \n", response);

    return true;
}


/** 
 *   send_text
 */
bool send_text(int sockfd, char *text)
{
    const size_t DATA_SIZE = 100;
    char write_data[DATA_SIZE];

    size_t write_data_size;

    build_client_text(text,  (char *)write_data, &write_data_size);

    bool ret = frame_write(sockfd, (char *)write_data, write_data_size);

    if(!ret){
        return false;
    }

    frame_read(sockfd);

    return true;
}


/** 
 *   send_close
 */
bool send_close(int sockfd, int code,  char *reason)
{

    const size_t MARGIN = 10;

    size_t reason_len = 0;

    if(reason){
        reason_len = strlen(reason);
    }

    size_t data_size =  reason_len + FRAME_BASE_SIZE +FRAME_CLOSE_CODE_SIZE +  MARGIN;

    char write_data[data_size];

    printf("send close: %d : %s \n", code, reason);

    size_t write_data_size;

    build_client_close(code, reason, (char*)write_data,  &write_data_size );

    bool ret = frame_write(sockfd, (char *)write_data, write_data_size);

    if(!ret){
        return false;
    }

    frame_read(sockfd);

    return true;
}


/** 
 *   send_ping
 */
bool send_ping(int sockfd)
{
    const size_t DATA_SIZE = 100;
    char write_data[DATA_SIZE];

    size_t write_data_size;

    build_client_ping((char*)write_data,  &write_data_size );

    bool ret = frame_write(sockfd, (char *)write_data, write_data_size);

    if(!ret){
        return false;
    }

    frame_read(sockfd);

    return true;
}


/** 
 *   frame_read
 */
bool frame_read(int sockfd)
{
    const char NUL = '\0';

    const size_t DATA_SIZE = 100; 
    char read_data[DATA_SIZE];

    memset(read_data, NUL, DATA_SIZE);


    ssize_t read_size;

    int err;

    for(int i=0; i<10; i++)
    {
        sleep(5);
        read_size = tcp_read( sockfd, (char *)read_data, DATA_SIZE, &err );
        if(read_size>0){
            break;
        }
    }// for

    if(read_size<0){
        printf("tcp_read: %s \n", strerror(err) );
        return false;
    } else if(read_size == 0){
        printf("tcp_read: no data \n");
        return true;
    }

    dump_frame_read_data(read_data, read_size);

    parse_frame( read_data,  read_size);

    return true;
}



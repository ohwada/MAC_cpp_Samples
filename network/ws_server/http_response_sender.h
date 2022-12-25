#pragma once
/**
 * http_response_sender.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include "http_response_builder.h"
#include "file_util.h"
#include "tcp.h"


// prototype
void send_response_text(int sockfd_client, char* text, char *mime);
bool send_response_file(int sockfd_client, char* file);


/**
 *  send_response_text
 */
void send_response_text(int sockfd_client, char* text, char *mime)
{
    const size_t BUFSIZE = 1024; // 1KB
    char header[BUFSIZE];
    char error[BUFSIZE];

    printf("%s \n", text);
    printf("%s \n", mime);

    int length = (int)strlen(text);
    bool is_crlf = true; 
   
    build_response_header_ok(length, mime, is_crlf, (char *)header);

    printf("\n response header \n");
    printf("%s \n", header);

// send fixed prepared response
bool ret1 = tcp_write_str( sockfd_client, (char *)header, (char *)error );
    if(!ret1) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

bool ret2 = tcp_write_str( sockfd_client, text, (char *)error );
    if(!ret2) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

}


/**
 *  send_response_file
 */
bool send_response_file(int sockfd_client, char* file)
{

    const size_t BUFSIZE = 1024; // 1KB
    char header[BUFSIZE];
    char error[BUFSIZE];

    build_response_header_ok_from_file(file, (char *)header);

    printf("\n response header \n");
    printf("%s \n", header);

    size_t data_size;
    char* data = file_binary_read(file, &data_size, (char *)error);
    if(!data){
        fprintf(stderr, "cannot read: %s : %s \n", file, error);
        return false;
    }

    bool ret1 = tcp_write_str( sockfd_client, (char *)header, (char *)error );
    if(!ret1) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

    bool ret2 = tcp_write( sockfd_client, (char *)data, data_size, (char *)error );
    if(!ret2) {
        fprintf(stderr, "tcp_write: %s \n", error );
    }

    free(data);
    return true;
}


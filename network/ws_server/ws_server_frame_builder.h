#pragma once
/**
 * ws_server_frame_builder.h
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws_frame.h"
#include "ws_frame_common.h"


// prototype
void build_server_text( char* text, char* data, size_t *data_size_ret);
void build_server_close(int code, char *reason, char* data, size_t *data_size_ret);
void build_server_frame(char opcode, char *payload, size_t payload_len, char* data, size_t *data_size);


/**
 * build_server_text
 */
void build_server_text( char* text, char* data, size_t *data_size_ret)
{
    const char NUL = '\0';

    size_t text_len = strlen(text);

    size_t data_size = text_len + FRAME_BASE_SIZE;

    *data_size_ret = data_size;

    memset(data, NUL,  data_size );

    data[0] = (unsigned char)(  B_FIN | OP_TEXT );

    data[1] = (unsigned char)text_len;

    for( int i=0; i<text_len; i++){
         data[FRAME_BASE_SIZE + i] =  text[i];
    }

}


/**
 * build_server_close
 */
void build_server_close(int code, char *reason, char* data, size_t *data_size)
{

    size_t reason_len = strlen(reason);

    size_t payload_len =  reason_len +FRAME_CLOSE_CODE_SIZE;

    char payload[payload_len+1];

    char byte0;
    char byte1;

    int_to_bytes(code, &byte0, &byte1);

    payload[0] = byte0;
    payload[1] = byte1;

    memcpy(&payload[FRAME_CLOSE_CODE_SIZE], reason, reason_len);

    build_server_frame(OP_CLOSE, payload, payload_len, data, data_size);

}


/**
 * build_server_frame
 */
void build_server_frame(char opcode, char *payload, size_t payload_len, char* data, size_t *data_size)
{

    const size_t FRAME_BASE_SIZE = 2;

      *data_size = FRAME_BASE_SIZE + payload_len;

    data[0] =  (unsigned char)(B_FIN | opcode) ;

    data[1] = (unsigned char)payload_len;

    memcpy( &data[FRAME_BASE_SIZE], payload, payload_len);

}


/**
 * build_srver_pong
 */
void build_server_pong(char* data, size_t *data_size_ret)
{
  
      *data_size_ret = FRAME_BASE_SIZE;

    data[0] =  (unsigned char)(B_FIN | OP_PONG) ;

    data[1] = 0x00;

}


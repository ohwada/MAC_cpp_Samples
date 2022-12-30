#pragma once
/**
 * ws_client_frame_builder.h
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws_frame.h"
#include "ws_frame_common.h"
#include "random_char.h"


// prototype
void build_client_text(char* payload,  char* data, size_t *data_size);
void build_client_close(int code, char* reason, char* data, size_t *data_size);
void build_client_ping(char* data, size_t *data_size_ret);
void build_client_frame(char opcode, char *payload, size_t payload_len, char* data, size_t *data_size);
void gen_rand_mask(char* mask, size_t size);


/**
 * build_client_text
 */
void build_client_text( char* text, char* data, size_t *data_size)
{
    build_client_frame(OP_TEXT, text, strlen(text), data, data_size);
}


/**
 * build_client_close
 */
void build_client_close(int code, char* reason, char* data, size_t *data_size)
{
    if(code == 0){
        build_client_frame(OP_CLOSE, NULL, 0, data, data_size);
        return;
    }

    size_t reason_len = 0;

    if(reason){
        reason_len = strlen(reason);
    }

    size_t payload_len =  reason_len + FRAME_CLOSE_CODE_SIZE;

    // printf(" payload_len: %zu \n",  payload_len);

    char payload[payload_len+1];

    char byte0;
    char byte1;

    int_to_bytes(code, &byte0, &byte1);

    payload[0] = byte0;

    payload[1] = byte1;

    memcpy(&payload[FRAME_CLOSE_CODE_SIZE], reason, reason_len);

    build_client_frame(OP_CLOSE, payload, payload_len, data, data_size);

}


/**
 * build_client_ping
 */
void build_client_ping(char* data, size_t *data_size)
{
    build_client_frame(OP_PING, NULL, 0, data, data_size);
}


/**
 * build_client_frame
 */
void build_client_frame(char opcode, char *payload, size_t payload_len, char* data, size_t *data_size)
{
    char mask[FRAME_MASK_SIZE];

    const size_t OFFSET = FRAME_BASE_SIZE + FRAME_MASK_SIZE;


    gen_rand_mask( (char *)mask,  FRAME_MASK_SIZE);

      *data_size = FRAME_BASE_SIZE + FRAME_MASK_SIZE + payload_len;

    data[0] =  (unsigned char)(B_FIN | opcode) ;

    data[1] = (unsigned char)(B_MASK | payload_len);

  for( int i=0; i<FRAME_MASK_SIZE; i++){
         data[i+FRAME_BASE_SIZE] =  mask[i];
    }

    if((payload_len == 0)||(!payload)){
        return;
    }

    for( int i=0; i<  payload_len; i++){
         data[OFFSET+i] =   payload[i] ^ mask[i % 4];
    }

}


/**
 * gen_rand_mask
 */
void gen_rand_mask(char* mask, size_t size)
{
    for(int i=0; i<size; i++){
        mask[i] = getRandomCharMix();
    }
}



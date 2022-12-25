#pragma once
/**
 * ws_frame_parser.h
 * 2022-10-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ws_frame.h"
#include "ws_frame_common.h"

// prototype
char parse_frame(char* data, size_t data_size);
bool parse_text(char* data,  size_t data_size, char* text);
bool parse_close(char* data, size_t data_size, int *code, char *reason);
char parse_opcode(char* data);
size_t parse_payload_length(char* data);
bool parse_payload(char* data,  size_t data_size, char* payload );



/**
 * parse_frame
 */
char parse_frame(char* data, size_t data_size)
{

    const size_t MARGIN = 10; 

    size_t payload_len = parse_payload_length(data);

    char text[payload_len+MARGIN];
    char reason[payload_len+MARGIN];

    char opcode = parse_opcode(data);

    if ( opcode == OP_TEXT) {
        parse_text(data, data_size, (char *)text );
        printf("r text: %s \n", text);
    } else if ( opcode == OP_CLOSE) {
        int code;
        bool ret = parse_close(
        data, data_size, &code, (char *)reason);
        if(ret){
            printf("r %s(%d): %s \n",  
            closecode_to_string(code), code, reason);
        } else {
            printf("r: Close without code \n");
        }
    } else if ( opcode == OP_PING){
        printf("r: Ping \n");
    } else if ( opcode == OP_PONG){
        printf("r: Pong \n");
    }

    return opcode;
}


/**
 * parse_text
 */
bool parse_text(char* data,  size_t data_size, char* text)
{
    const char NUL = '\0';

    size_t payload_len = parse_payload_length(data);

    if(payload_len <= 0){
        return false;
    }

    if(payload_len > data_size) {
        return false;
    }

    char payload[payload_len];

    bool ret = parse_payload(data,  data_size, (char *)payload);

    if(!ret){
        return false;
    }

    memcpy(text, payload, payload_len);

    text[payload_len] = NUL;

    return true;
}


/**
 * parse_close
 */
bool parse_close(char* data, size_t data_size, int *code, char *reason)
{
    const char NUL = '\0';

size_t payload_len = parse_payload_length(data);

    if(payload_len < FRAME_CLOSE_CODE_SIZE){
        return false;
    }

    if(payload_len > data_size) {
        return false;
    }

    char payload[payload_len];

    bool ret = parse_payload(data,  data_size, (char *)payload);

    if(!ret){
        return false;
    }

    *code = bytes_to_int( payload[0], payload[1] );

    if(payload_len == FRAME_CLOSE_CODE_SIZE){
       reason[0] = NUL;
        return true;
    }

    size_t reason_len = payload_len - FRAME_CLOSE_CODE_SIZE;

    memcpy(reason, &payload[FRAME_CLOSE_CODE_SIZE], reason_len);

    reason[reason_len] = NUL;

    return true;
}


/**
 * parse_opcode
 */
char parse_opcode(char* data)
{
   char opcode = data[0] & OPCODE_MASK;
    return opcode;
}


/**
 * parse_payload_length
 */
size_t parse_payload_length(char* data)
{
    size_t len = (size_t)(data[1] & PAYLOAD_LEN_MASK);
    return len;
}


/**
 * parse_payload
 */
bool parse_payload(char* data,  size_t data_size, char* payload_ret)
{

    size_t payload_len = parse_payload_length(data);

    char mask_bit = data[1] & B_MASK;

    if(payload_len <= 0){
        return false;
    }

    if(payload_len > data_size) {
        return false;
    }

    char payload[payload_len];

    if(mask_bit){
        for(int i=0; i<payload_len; i++){
                int j1 = FRAME_BASE_SIZE + FRAME_MASK_SIZE + i;
                int j2 =   FRAME_BASE_SIZE + (i % 4);
                payload[i] = data[j1] ^ data[j2];
        } // for
    } else {
        memcpy(payload, &data[FRAME_BASE_SIZE], payload_len);
    }

    memcpy(payload_ret, payload, payload_len);

    return true;
}


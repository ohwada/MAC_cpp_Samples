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
char parse_opcode(char* data);
bool parse_text(char* data,  size_t data_size, char* text);
bool parse_close(char* data, size_t data_size, int *code, char *reason);



/**
 * parse_frame
 */
char parse_frame(char* data, size_t data_size)
{

    const size_t DATA_SIZE = 100; 
    char text[DATA_SIZE];
    char reason[DATA_SIZE];

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
 * parse_opcode
 */
char parse_opcode(char* data)
{
   char opcode = data[0] & OPCODE_MASK;
    return opcode;
}


/**
 * parse_text
 */
bool parse_text(char* data,  size_t data_size, char* text)
{
    const char NUL = '\0';

    unsigned char payload_len = data[1] & PAYLOAD_LEN_MASK;

    char mask_bit = data[1] & B_MASK;

    if(payload_len <= 0){
        return false;
    }

    if(mask_bit){
        for(int i=0; i<payload_len; i++){
                int j1 = FRAME_BASE_SIZE + FRAME_MASK_SIZE + i;
                int j2 =   FRAME_BASE_SIZE + (i % 4);
                text[i] = data[j1] ^ data[j2];
        } // for
    } else {
        memcpy(text, &data[FRAME_BASE_SIZE], payload_len);
    }
    text[payload_len] = NUL;

    return true;
}


/**
 * parse_close
 */
bool parse_close(char* data, size_t data_size, int *code, char *reason)
{
    const char NUL = '\0';

    char payload_len = data[1] & PAYLOAD_LEN_MASK;

    char mask_bit = data[1] & B_MASK;

    if(payload_len <= 0){
        return false;
    }

    if(payload_len == 2){
    }
    size_t buf_len = payload_len+1;
    char buf[buf_len];
    memset(buf, NUL, buf_len);

        if(mask_bit){
                    for(int i=0; i<payload_len; i++){
                        int j1 = FRAME_BASE_SIZE + FRAME_MASK_SIZE + i;
                        int j2 =   FRAME_BASE_SIZE + (i % 4);
                        buf[i] = data[j1] ^ data[j2];
                    } // for
        } else {
                memcpy(buf, &data[FRAME_BASE_SIZE], payload_len);
        }

    *code = bytes_to_int(buf[0], buf[1]);

    size_t reason_len = payload_len - FRAME_CLOSE_CODE_SIZE;

    if(payload_len > 2){
        memcpy(reason, &buf[FRAME_CLOSE_CODE_SIZE], reason_len);
    } else if(payload_len == 2){
        reason[0] = NUL;
    }

    return true;
}



#pragma once
/**
 * ws_frame_parser.hpp
 * 2022-10-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <boost/format.hpp>
#include "ws_frame.h"
#include "ws_frame_common.hpp"

// prototype
char parse_frame(char* data, size_t data_size);
bool parse_text(char* data,  size_t data_size, std::string &text);
bool parse_close(char* data, size_t data_size, int &code,std::string  &reason);
char parse_opcode(char* data);
size_t parse_payload_length(char* data);
 std::vector<char>  parse_payload(char* data,  size_t data_size);


/**
 * parse_frame
 */
char parse_frame(char* data, size_t data_size)
{

    const char SPACE = ' '; 
    const size_t DATA_SIZE = 100;

    std::string text(SPACE, DATA_SIZE);
    std::string reason(SPACE, DATA_SIZE);

        int close_code;

    char opcode = parse_opcode(data);

    if ( opcode == OP_TEXT) {
        parse_text(data, data_size, text );
       std::cout << "r text: " << text << std::endl;
    } else if ( opcode == OP_CLOSE) {
        bool ret = parse_close(
        data, data_size, close_code, reason);
            if(ret){
                print_close("r", close_code, reason);
            } else {
                std::cout << "r: Close without code" << std::endl;
            }
    } else if ( opcode == OP_PING){
        std::cout << "r: Ping" << std::endl;
    } else if ( opcode == OP_PONG){
        std::cout << "r: Pong" << std::endl;
    }

    return opcode;
}


/**
 * parse_text
 */
bool parse_text(char* data,  size_t data_size, std::string &text_ret)
{
    auto payload = parse_payload(data, data_size);

    if(payload.size() == 0){
        return false;
    }

    std::string text(payload.begin(), payload.end() );
    text_ret = text;

    return true;
}


/**
 * parse_close
 */
bool parse_close(char* data, size_t data_size, int &code, std::string &reason)
{

    auto payload = parse_payload(data, data_size);

    auto payload_len = payload.size();
    if(payload_len < FRAME_CLOSE_CODE_SIZE){
        return false;
    }

    code = bytes_to_int(payload[0], payload[1]);

    if(payload_len == FRAME_CLOSE_CODE_SIZE){
        reason = "";
        return true;
    }

    for(int i=0; i<payload_len; i++){
        int j= i+ FRAME_CLOSE_CODE_SIZE;
        reason[i] = payload[j];
    }

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
    unsigned char len = data[1] & PAYLOAD_LEN_MASK;
    return (size_t)len;
}


/**
 * parse_payload
 */
 std::vector<char> parse_payload(char* data,  size_t data_size)
{

    auto payload_len = parse_payload_length(data);

    char mask_bit = data[1] & B_MASK;

    if(payload_len <= 0){
        std::vector<char> vec;
        return vec;
    }

    std::vector<char> payload(payload_len);

    std::string res;

    if(mask_bit){
        for(int i=0; i<payload_len; i++){
                int j1 = FRAME_BASE_SIZE + FRAME_MASK_SIZE + i;
                int j2 =   FRAME_BASE_SIZE + (i % 4);
                payload[i] = data[j1] ^ data[j2];
        } // for
    } else {
        for(int i=0; i<payload_len; i++){
                int j = FRAME_BASE_SIZE + i;
                payload[i] = data[j];
        } // for
    }

    return payload;
}


#pragma once
/**
 * ws_client_frame_builder.hpp
 * 2022-10-01 K.OHWADA
 */

#include <string>
#include <vector>
#include "ws_frame.h"
#include "ws_frame_common.hpp"
#include "random_string.hpp"


// prototype
std::vector<char> build_client_text( std::string text);
std::vector<char> build_client_close(int code, std::string reason);
std::vector<char> get_client_ping();
std::vector<char> get_client_pong();
std::vector<char> build_client_frame(char opcode, std::vector<char> payload);


/**
 * build_client_text
 */
std::vector<char> build_client_text( std::string text)
{

    std::vector<char> payload(text.begin(), text.end());

    return build_client_frame(OP_TEXT, payload);
}


/**
 * build_client_close
 */
std::vector<char> build_client_close(int code, std::string reason)
{

    std::vector<char> payload(FRAME_CLOSE_CODE_SIZE);

    char byte0;
    char byte1;

    int_to_bytes(code, &byte0, &byte1);

    payload[0] = byte0;
    payload[1] = byte1;

    std::vector<char> vec(reason.begin(), reason.end());

    payload.insert( payload.end(), vec.begin(), vec.end() );

    return build_client_frame(OP_CLOSE, payload);
}


/**
 * build_client_ping
 */
std::vector<char> get_client_ping()
{
    std::vector<char> payload;
    return build_client_frame(OP_PING, payload);
}


/**
 * build_client_pong
 */
std::vector<char> get_client_pong()
{
    std::vector<char> payload;
    return build_client_frame(OP_PONG, payload);
}


/**
 * build_client_frame
 */
std::vector<char> build_client_frame(char opcode, std::vector<char> payload)
{
    const size_t OFFSET = FRAME_BASE_SIZE + FRAME_MASK_SIZE;

    auto payload_len = payload.size();

    size_t data_size = FRAME_BASE_SIZE + FRAME_MASK_SIZE + payload_len;

 auto mask = genRandomStringMix(FRAME_BASE_SIZE);

    std::vector<char> data(data_size);

    data[0] =  (unsigned char)(B_FIN | opcode) ;

    data[1] = (unsigned char)(B_MASK | payload_len);

  for( int i=0; i<FRAME_MASK_SIZE; i++){
         data[i+FRAME_BASE_SIZE] =  mask[i];
    }

    if(payload_len == 0){
        return data;
    }

    for( int i=0; i<  payload_len; i++){
         data[OFFSET+i] =   payload[i] ^ mask[i % 4];
    }

    return data;
}





#pragma once
/**
 * ws_server_frame_builder.hpp
 * 2022-10-01 K.OHWADA
 */

#include <string>
#include <vector>
#include "ws_frame.h"
#include "ws_frame_common.h"


// prototype
std::vector<char> build_server_text( std::string text);
std::vector<char> build_server_close(int code, std::string reason);
std::vector<char> build_server_frame(char opcode, std::vector<char> payload);
std::vector<char> get_server_ping();
std::vector<char> get_server_pong();
std::vector<char> build_server_frame_without_payload(char opcode);


/**
 * build_server_text
 */
std::vector<char> build_server_text( std::string text)
{

    std::vector<char> payload(text.begin(), text.end());

    return build_server_frame(OP_TEXT, payload);
}


/**
 * build_server_close
 */
std::vector<char> build_server_close(int code, std::string reason)
{

    std::vector<char> payload(FRAME_CLOSE_CODE_SIZE);

    char byte0;
    char byte1;

    int_to_bytes(code, &byte0, &byte1);

    payload[0] = byte0;
    payload[1] = byte1;

    std::vector<char> vec(reason.begin(), reason.end());

    payload.insert( payload.end(), vec.begin(), vec.end() );

    return build_server_frame(OP_CLOSE, payload);
}


/**
 * build_server_frame
 */
std::vector<char> build_server_frame(char opcode, std::vector<char> payload)
{

    auto payload_len = payload.size();

    std::vector<char> data( FRAME_BASE_SIZE);

    data[0] =  (unsigned char)(B_FIN | opcode) ;

    data[1] = (unsigned char)payload_len;

    data.insert( data.end(), payload.begin(), payload.end() );

    return data;
}


/**
 * get_server_ping
 */
std::vector<char> get_server_ping()
{
      return build_server_frame_without_payload(OP_PING);
}


/**
 * get_server_pong
 */
std::vector<char> get_server_pong()
{
    return build_server_frame_without_payload(OP_PONG);
}


/**
 *  build_server_frame_without_payload
 */
std::vector<char> build_server_frame_without_payload(char opcode)
{
  
    std::vector<char> data(FRAME_BASE_SIZE);

    data[0] =  (unsigned char)(B_FIN | opcode) ;

    data[1] = 0x00;

    return data;
}



#pragma once
/**
 * ws_server.hpp
 * 2022-10-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
#include "http_response_builder.hpp"
#include "ws_request_parser.hpp"
#include "ws_response_builder.hpp"
#include "ws_server_frame_builder.hpp"
#include "ws_frame_parser.hpp"
#include "ws_frame_common.hpp"
#include "ws_util.hpp"

// prototype
std::vector<char> proc_text(char *read_data, size_t data_size );
std::vector<char> proc_close(char *read_data, size_t data_size);
std::vector<char> proc_ping(char *read_data, size_t data_size);
std::vector<char> proc_pong(char *read_data, size_t data_size);


/**
 *  enum response
 */
enum response {
    RES_NONE = 0,
    RES_HANDSHAKE = 1,
    RES_BRAWSER = 2,
    RES_TEXT = 3,
    RES_FRAME = 4,
};


/**
 *  enum mode
 */
enum mode {
    MODE_NORMAL = 0,
    MODE_ECHO = 1,
    MODE_TEST = 2,
};


/**
 * proc_text
 */
std::vector<char> proc_text(char *read_data, size_t read_data_size)
{

    std::vector<char> res;

    std::string text;

    bool ret = parse_text( (char *)read_data, read_data_size, text);

    if(!ret){
        std::cout << "cannot parse text" << std::endl;
        return res;
    }

    std::vector<char> vec(text.begin(), text.end() );
    return vec;
 
}


/**
 * proc_close
 */
std::vector<char> proc_close(char *read_data, size_t read_data_size)
{
bool is_send_close = false;

    std::vector<char> vec;

    if( !is_send_close){
        return vec;
    }

    int recv_code = 0;
    int send_code = 0;

    std::string reason;

    bool ret = parse_close(read_data, read_data_size, recv_code, reason);

    if(ret){
        send_code = recv_code;
      } else {
        send_code = CLOSE_NORMAL;
        reason = "";
     }

// send back
    auto res = build_server_close(send_code, reason);

    print_close("send", send_code, reason);
    return res;
}


/**
 * proc_ping
 */
std::vector<char> proc_ping(char *read_data, size_t read_data_size)
{
// send Pong always
    auto res = get_server_pong();
    std::cout << "send Pong" << std::endl;
    return res;
}


/**
 * proc_pong
 */
std::vector<char> proc_pong(char *read_data, size_t read_data_size)
{
// always ignore
    std::vector<char> vec;
    return vec;
}


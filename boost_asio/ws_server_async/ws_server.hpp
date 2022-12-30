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
std::vector<char> proc_text(char *read_data, size_t data_size, int mode );
std::vector<char> proc_close(char *read_data, size_t data_size, int mode );
std::vector<char> proc_ping(char *read_data, size_t data_size, int mode);
std::vector<char> proc_pong(char *read_data, size_t data_size, int cnt, int limit, int mode);


/**
 *  enum response
 */
enum response {
    RES_NONE = 0,
    RES_HANDSHAKE = 1,
    RES_BRAWSER = 2,
    RES_FRAME = 3,
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
std::vector<char> proc_text(char *read_data, size_t read_data_size, int mode )
{

    std::vector<char> res;

    std::string text;

    bool ret = parse_text( (char *)read_data, read_data_size, text);

    if(!ret){
        std::cout << "cannot parse text" << std::endl;
        return res;
    }


    if(mode == MODE_ECHO) {
// echo back
        res = build_server_text(text);    
        std::cout <<"send text: " << text << std::endl;
    } else if(mode == MODE_TEST) {
// send back ping
        res = get_server_ping();    
        std::cout <<"send Ping" << std::endl;
    } else {
// return empty
        return res;
    }

    return res;
}


/**
 * proc_close
 */
std::vector<char> proc_close(char *read_data, size_t read_data_size, int mode )
{

    std::vector<char> vec;

    if(mode != MODE_ECHO) {
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
std::vector<char> proc_ping(char *read_data, size_t read_data_size, int mode )
{
// send Pong always

    auto res = get_server_pong();

    std::cout << "send Pong" << std::endl;
    return res;
}


/**
 * proc_pong
 */
std::vector<char> proc_pong(char *read_data, size_t read_data_size, int cnt, int limit, int mode )
{
// when Test mode
// send text until limit is reached
// send close when the limit is reached
// when not Test mode
// send nothing

    const std::string FORMAT("Test %03d");

    int code = CLOSE_NORMAL;
    std::string reason;

    std::vector<char> res;

    if(mode == MODE_TEST) {
        if(cnt > limit){
// send close
            res = build_server_close(code, reason);
            print_close("send", code, reason);
        } else {
// send new text
            auto text = boost::str( boost::format(FORMAT) % cnt);
            res = build_server_text(text);
            std::cout << "send text: " << text << std::endl;
        }
    } else {
// send nothing
    }

     return res;
}


#pragma once
/**
 * ws_client.hpp
 * 2022-10-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "ws_response_parser.hpp"
#include "ws_client_frame_builder.hpp"
#include "ws_frame_parser.hpp"
#include "ws_frame_common.hpp"
#include "ws_util.hpp"

// prototype
bool check_handshake_response(char *data,  size_t bytes_transferred);
std::vector<char> proc_handshake_response(std::string text, int mode);
std::vector<char> proc_text(char *read_data, size_t data_size, int mode );
std::vector<char> proc_close(char *read_data, size_t data_size, int mode );
std::vector<char> proc_ping(char *read_data, size_t data_size, int mode);
std::vector<char> proc_pong(char *read_data, size_t data_size, int cnt, int limit, int mode);
void print_close( std::string prefix, int code, std::string reason);
std::string close_to_string( int code, std::string reason);
void dump_vec(std::vector<char> vec);


/**
 *  enum mode
 */
enum mode {
    MODE_NORMAL = 0,
    MODE_ECHO = 1,
};


/**
 *  check_handshake_response
 */
bool check_handshake_response(char *data,  size_t bytes_transferred)
{
   std::string EXPECT_CODE("101");

    std::string response(data,  bytes_transferred);
    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    auto code = parse_status_code(response );
    std::cout << "status_code: " << code << std::endl;

    auto accept_key = parse_accept_key(response );
    std::cout << "accept_key: " << accept_key << std::endl;

    if(code != EXPECT_CODE){
        return false;
    }
 
    bool ret = (accept_key.size() > 0)? true: false;
    return ret;
}


/**
 *  proc_handshake_response
 */
std::vector<char> proc_handshake_response(std::string text, int mode)
{

    std::vector<char> res;

    if(mode == MODE_NORMAL){
// send text
        res = build_client_text(text);
        std::cout << "send text: " << text << std::endl;
    } else if(mode == MODE_ECHO){
// send nothing
    }

    return res;
}


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

    if (mode == MODE_NORMAL) {
        res = get_client_ping();
        std::cout << "send Ping" << std::endl;
    } else if (mode == MODE_ECHO){
// echo back
        res = build_client_text(text);
        std::cout <<"send text: " << text << std::endl;
    }

    return res;
}


/**
 * proc_close
 */
std::vector<char> proc_close(char *read_data, size_t read_data_size, int mode )
{

    std::vector<char> vec;

    int recv_code = 0;
    int send_code = 0;

    std::string reason;

    bool ret = parse_close(read_data, read_data_size, recv_code, reason);

    if(ret){
        send_code = recv_code;
      } else {
        send_code = CLOSE_NORMAL;
     }

   if (mode == MODE_NORMAL) {
        return vec;
    }

// echo back
 auto res = build_client_close(send_code, reason);

    print_close("send", send_code, reason);
    return res;
}


/**
 * proc_ping
 */
std::vector<char> proc_ping(char *read_data, size_t read_data_size, int mode )
{    
// send back pong always

    auto res = get_client_pong();

    std::cout << "send Pong" << std::endl;
    return res;
}


/**
 * proc_pong
 */
std::vector<char> proc_pong(char *read_data, size_t read_data_size, int cnt, int limit, int mode )
{    
// when Normal mode
// send new text until limit is reached
// send close when the limit is reached
// when other mode
// wait to next message

    int code = CLOSE_NORMAL;
    std::string reason;

    std::vector<char> res;

    if(mode == MODE_NORMAL) {
        if(cnt > limit) {
// send back close
            res = build_client_close(code, reason);
            print_close("send", code, reason);
        } else {
// send new text
            auto text = build_msg_text(cnt);
            res = build_client_text(text);
            std::cout << "send text: " << text << std::endl;
        }
    } // mode

    return res;
}


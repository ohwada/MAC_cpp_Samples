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
std::vector<char> proc_handshake_response(std::string text);
std::vector<char> proc_text(char *read_data, size_t data_size);
std::vector<char> proc_close(char *read_data, size_t data_size);
std::vector<char> proc_ping(char *read_data, size_t data_size);
std::vector<char> proc_pong(char *read_data, size_t data_size);
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
std::vector<char> proc_handshake_response(std::string text)
{
// always none
    std::vector<char> res;
    return res;
}


/**
 * proc_text
 */
std::vector<char> proc_text(char *read_data, size_t read_data_size)
{
// always none
    std::vector<char> res;
    return res;
}


/**
 * proc_close
 */
std::vector<char> proc_close(char *read_data, size_t read_data_size)
{
// send back close

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
    print_close("send", send_code, reason);
    auto res = build_client_close(send_code, reason);
    return res;
}


/**
 * proc_ping
 */
std::vector<char> proc_ping(char *read_data, size_t read_data_size)
{    
// send back pong always

    auto res = get_client_pong();

    std::cout << "send Pong" << std::endl;
    return res;
}


/**
 * proc_pong
 */
std::vector<char> proc_pong(char *read_data, size_t read_data_size)
{    
// always none
    std::vector<char> res;
    return res;
}


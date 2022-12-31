/**
 * ws_chat_server.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/chat_server.cpp

#include <iostream>
#include "ws_chat_server.hpp"
#include "port.h"


/**
 *  do_handle_read_handshake
 */
int do_handle_read_handshake(char* data,  size_t bytes_transferred,  std::string &write_data)
{
// If the request have "Sec-WebSocket-Key" header, 
// send back the handshake response.
//  as WebSocket opening handshake
// If the request doesn't have "Sec-WebSocket-Key" header, 
// send back index.html, 
// considered as access from a Web Browser

std::cout << "do_handle_read_handshake" << std::endl;

    std::string request(data, bytes_transferred);

   std::cout << std::endl;
   std::cout << "request" << std::endl;
   std::cout << request << std::endl;

    auto sec_key = parse_seckey(request);
    if ( sec_key.empty() ){
        std::cout << "no sec key" << std::endl;
        std::string file("www/index.html");
        auto res = build_response_file(file);
        write_data = res;
        std::cout << "send index.html" << std::endl;
        return RES_BRAWSER;
    }

    std::cout << "sec_key: " << sec_key << std::endl;
   auto accept_key = gen_accept_key(sec_key);
    std::cout << "accept_key: " << accept_key << std::endl;

    auto res = ws_build_response(accept_key);
    write_data = res;
    std::cout <<  "response" << std::endl;
    std::cout << res << std::endl;
    return RES_HANDSHAKE;
}


/**
 *  do_handle_read_frame
 */
int do_handle_read_frame(char* data,  size_t bytes_transferred, std::vector<char> &write_data)
{
    const int SLEEP = 1000; // 1 sec

    std::vector<char> res;

    std::cout << std::endl;
    dump_frame_read_data(data,  bytes_transferred);


    auto opcode = parse_frame(data, bytes_transferred);

    if(opcode == OP_TEXT){
                res = proc_text(data, bytes_transferred);
                write_data = res;
                return RES_TEXT;
    } else if(opcode == OP_CLOSE){
               res =  proc_close(data, bytes_transferred);
    } else if(opcode == OP_PING){
                res = proc_ping(data, bytes_transferred);
    } else if(opcode == OP_PONG){
                res = proc_ping(data, bytes_transferred);
    }
   
    write_data = res;
    thread_sleep( SLEEP );
    return RES_FRAME ;
}


/**
 * server_text
 */
std::vector<char> server_text( std::string text)
{
        std::cout << "send text: " << text << std::endl;
        return build_server_text( text );
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
     unsigned short port = PORT;

    if (argc == 2) {
        port = atoi(argv[1]);
    } else {
        cout << "Usage: chat_server <port> " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port);

  return 0;
}

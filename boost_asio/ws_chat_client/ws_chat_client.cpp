/**
 * ws_chat_client.cpp
 * 2022-10-01 K.OHWADA
 */


// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/chat_client.cpp


#include <iostream>
#include "ws_chat_client.hpp"
#include "port.h"


/**
 *  do_handle_read_response
 */
std::vector<char>  do_handle_read_response(char* data, size_t bytes_transferred)
{
    std::vector<char> res;

    check_handshake_response(data, bytes_transferred);

// send nothing
    return res;
}


/**
 *  do_handle_read_frame
 */
std::vector<char> do_handle_read_frame(char* data,  size_t bytes_transferred)
{
    const int SLEEP = 1000; // 1 sec

    std::vector<char> res;

    std::cout << std::endl;
    dump_frame_read_data(data,  bytes_transferred);

    auto opcode = parse_frame(data, bytes_transferred);

    if(opcode == OP_TEXT){
                // none
    } else if(opcode == OP_CLOSE){
               res =  proc_close(data, bytes_transferred);
    } else if(opcode == OP_PING){
                res = proc_ping(data, bytes_transferred);
    } else if(opcode == OP_PONG){
        // none
    }

    thread_sleep( SLEEP );
    return res;
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string host("localhost");
    string port = std::to_string( PORT );
    string path("/");

    if (argc == 4) {
        host = argv[1];
        port = argv[2];
        path = argv[3];
    } else if (argc == 3) {
        host = argv[1];
        port = argv[2];
    } else {
      cout << "Usage: chat_client <host> <port> <path> " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;
    cout << "path: " << path << endl;

    ws_chat_client(host, port, path);

  return 0;
}

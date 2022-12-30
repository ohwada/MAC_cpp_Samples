/**
 *  ws_client_sync.cpp
 * 2022-10-01 K.OHWADA
 */

// Websocket Client using Boost.Asio
// In Normal mode
// send first Text after opening handshake
// send Ping when recieve Text
// send new Text  when recieve Pong
// send Close when reached the set value
// In Echo mode
// echo back Text  when recieve Text


#include <iostream>
#include <string>
#include "ws_client_async.hpp"
#include "ws_client.hpp"
#include "port.h"


// global
const int TEXT_LIMIT = 10;
int mode = MODE_NORMAL;
bool is_handshake = true;
int text_cnt = 0;


/**
 *  do_handle_read
 */
std::vector<char> do_handle_read(char* data,  size_t bytes_transferred)
{
    const int SLEEP = 1000; // 1 sec

    std::string text("Hello World");

    std::vector<char> res;

    if( is_handshake) 
    {
// ignore message if it's not handshake response
        bool ret = check_handshake_response(data, bytes_transferred);
        if(!ret){
            return res;
        }

// send first text
        res = proc_handshake_response(text, mode);
        is_handshake = false;
        thread_sleep( SLEEP );
        return res;
    }

    std::cout << std::endl;
    dump_frame_read_data(data,  bytes_transferred);

    auto opcode = parse_frame(data, bytes_transferred);

    if(opcode == OP_TEXT){
                res = proc_text(data, bytes_transferred, mode);
    } else if(opcode == OP_CLOSE){
               res =  proc_close(data, bytes_transferred, mode);
    } else if(opcode == OP_PING){
                res = proc_ping(data, bytes_transferred, mode);
    } else if(opcode == OP_PONG){
                text_cnt ++;
                res = proc_pong(data, bytes_transferred, text_cnt, TEXT_LIMIT, mode);
    }

    thread_sleep( SLEEP );
    return res;
}

 using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{
    string server("localhost");
    std::string port = std::to_string( PORT );
    string path("/");

    if (argc == 5) {
        server =  argv[1];
       port =  argv[2];
        path =  argv[3];
        mode =  std::atoi(argv[4] );
    } else if (argc == 4) {
        server =  argv[1];
       port =  argv[2];
        path =  argv[3];
    } else if (argc == 3) {
        server =  argv[1];
        port =  argv[2];
    } else {
      cout << "Usage: async_client <server> <port> <path> <mode> \n";
    }

    cout << "server: " << server << endl;
    cout << "port: " << port << endl;
    cout << "path: " << path << endl;
    cout << "mode: " << mode << endl;

    ws_client_async(server, port, path);

  return 0;
}

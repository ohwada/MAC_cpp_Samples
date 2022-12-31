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
int text_cnt = 0;


/**
 *  do_handle_read_response
 */
std::vector<char> do_handle_read_response(char* data,  size_t bytes_transferred, int mode)
{
// In Normal mode
// send first text
// In Echo mode
// wait next message

std::cout << "do_handle_read_response: " << mode << std::endl;

    const int SLEEP = 1000; // 1 sec

    std::string text("Hello World");

    std::vector<char> res;

// ignore message if it's not handshake response
        bool ret = check_handshake_response(data, bytes_transferred);
        if(!ret){
            return res;
        }

    res = proc_handshake_response(text, mode);
    thread_sleep( SLEEP );
    return res;
}


/**
 *  do_handle_read_frame
 */
std::vector<char> do_handle_read_frame(char* data,  size_t bytes_transferred, int mode)
{
    const int SLEEP = 1000; // 1 sec

    std::vector<char> res;

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
    int mode = MODE_NORMAL;

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

    ws_client_async(server, port, path, mode);

  return 0;
}


// request
// GET / HTTP/1.1
// Host: localhost
// response
// HTTP/1.1 101 Switching Protocols
// send text: Hello World
// write (17) : 81 8b 59 72 00 fe 11 17 6c 92 36 52 57 91 2b 1e 64 
// read(13) : 81 0b 48 65 6c 6c 6f 20 57 6f 72 6c 64 
// r text: Hello World

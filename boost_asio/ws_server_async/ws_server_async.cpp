/**
 *  ws_server_async.cpp
 * 2022-10-01 K.OHWADA
 */

// WebSocket Echo Server using Boost.Asio
// send back index.html when sccessed by Web Brawser  
// echo back text

 // In Echo mode
// echo back Text  when recieve Text

// In Test mode
// send first Text after opening handshake
// send Ping when recieve Text
// send new Text  when recieve Pong
// send Close when reached the set value


#include <iostream>
#include "ws_server_async.hpp"
#include "port.h"

//global
const int TEXT_LIMIT = 10;
int text_cnt = 0;


/**
 * do_handle_read_handshake
 */
int do_handle_read_handshake(char* data,  size_t bytes_transferred, std::string &write_data)
{
// If the request have "Sec-WebSocket-Key" header, 
// send back the handshake response.
//  as WebSocket opening handshake
// If the request doesn't have "Sec-WebSocket-Key" header, 
// send back index.html, 
// considered as access from a Web Browser

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
    std::cout << std::endl;
    std::cout <<  "response" << std::endl;
    std::cout << res << std::endl;
    return RES_HANDSHAKE;
}


/**
 *  do_handle_write_handshake
 */
std::vector<char> do_handle_write_handshake()
{
    const int SLEEP = 2000; // 2 sec
    std::string text("Hello World");

    std::cout << "send text: " << text << std::endl;
    auto res = build_server_text(text);
// spacing transmissions to avoid merging with handshake response
    thread_sleep(SLEEP);
    return res;
}


/**
 *  do_handle_read_frame
 */
  std::vector<char> do_handle_read_frame(char* data,  size_t bytes_transferred, int mode )
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

    unsigned short port = PORT;
    int mode = MODE_ECHO;

    if (argc == 3){
        port = std::atoi(argv[1]);
        mode = std::atoi(argv[2]);
    } else if (argc == 2){
        port = std::atoi(argv[1]);
    } else {
      cout << "Usage: http_server <port> <mode> " << endl;
    }

    cout << "port: " << port << endl;
    cout << "mode: " << mode << endl;

    run_server(port, mode);
 
  return 0;
}

/**
 * echo_client.cpp
 * 2022-06-01 K.OHWADA
 */

// change log
// 2022-06-01 K.OHWADA
// (1) add on_open
// and sends "hello" to the server
// (2)  on_message
// wait 1 second 
// and sends a number that increases by 1 to the server.

// original : https://github.com/zaphoyd/websocketpp/tree/master/examples/echo_client

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/format.hpp>
#include "echo_port.h"


typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;


// global
// 1sec
const int SLEEP = 1000;

const int MAX = 100;
int cnt = 0;


/**
 * on_message
 */
// This message handler will be invoked once for each incoming message. 
// It prints the message 
// wait 1 second 
// and sends a number that increases by 1 to the server.
void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    //std::cout << "on_message called with hdl: " << hdl.lock().get()
       std::cout   << "on_message: " << msg->get_payload()
              << std::endl;

cnt++;
if(cnt > MAX){
    return;
}

// 1 sec sleep
 std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));

      std::string str = boost::str( boost::format("%03d") % cnt ) ;
//size_t len = msg.length();

    websocketpp::lib::error_code ec;

        c->send(hdl, str, websocketpp::frame::opcode::text);

    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }

} // on_message


/**
 * on_open
 */
void on_open(client* c, websocketpp::connection_hdl hdl) 
{
       std::cout   << "on_open " << std::endl;

// sends "hello" to the server
      std::string msg = "Hello";
        c->send(hdl, msg, websocketpp::frame::opcode::text);
}



/**
 * main
 */
int main(int argc, char* argv[]) 
{
    // Create a client endpoint
    client c;

    std::string uri = "ws://localhost:" + std::to_string(PORT);

    if (argc == 2) {
        uri = argv[1];
    }

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize ASIO
        c.init_asio();

        // Register our message handler
        c.set_message_handler(bind(&on_message,&c,::_1,::_2));

        c.set_open_handler(bind(&on_open,&c,::_1));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 1;
        }

        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        c.connect(con);

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        c.run();
    
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

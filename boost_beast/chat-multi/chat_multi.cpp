/**
 * chat_multi.cpp
 * 2022-10-01 K.OHWADA
 */

// original : https://github.com/boostorg/beast/blob/develop/example/websocket/server/chat-multi/main.cpp

//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

//------------------------------------------------------------------------------
/*
    WebSocket chat server, multi-threaded

    This implements a multi-user chat room using WebSocket. The
    `io_context` runs on any number of threads, specified at
    the command line.

*/
//------------------------------------------------------------------------------

#include "listener.hpp"
#include "shared_state.hpp"

#include <boost/asio/signal_set.hpp>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <vector>
#include <boost/beast/version.hpp>

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    cout << "BOOST_BEAST_VERSION: " << BOOST_BEAST_VERSION << endl;

    string str_address("0.0.0.0");
    string str_port("8090");
    string doc_root(".");
    string str_threads("5");

    // Check command line arguments.
    if (argc == 5)
    {
        str_address = argv[1];
        str_port = argv[2];
        doc_root = argv[3];
        str_threads = argv[4];
} else {
        std::cerr <<
            "Usage: websocket-chat-multi <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    websocket-chat-server 0.0.0.0 8080 . 5\n";
    }

    cout << "str_address: " << str_address << endl;
    cout << "str_port: " << str_port << endl;
    cout << "doc_root: " << doc_root << endl;
    cout << "str_threads: " << str_threads << endl;

    auto address = net::ip::make_address(str_address);
    auto port = static_cast<unsigned short>(std::atoi(str_port.c_str()));
    auto const threads = std::max<int>(1, std::atoi(str_threads.c_str()));

    // The io_context is required for all I/O
    net::io_context ioc;

    // Create and launch a listening port
    boost::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        boost::make_shared<shared_state>(doc_root))->run();

      std::cout << "listen port: " << port << std::endl;

    // Capture SIGINT and SIGTERM to perform a clean shutdown
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&ioc](boost::system::error_code const&, int)
        {
            // Stop the io_context. This will cause run()
            // to return immediately, eventually destroying the
            // io_context and any remaining handlers in it.
            ioc.stop();
        });

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    ioc.run();

    // (If we get here, it means we got a SIGINT or SIGTERM)

    // Block until all the threads exit
    for(auto& t : v)
        t.join();

    return EXIT_SUCCESS;
}

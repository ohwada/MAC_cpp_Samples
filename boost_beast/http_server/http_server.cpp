/**
 * beast sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Server, synchronous

// g++ src/http_server.cpp -std=c++11 `pkg-config --cflags --libs boost`  


// original : https://github.com/boostorg/beast/blob/develop/example/http/server/sync/http_server_sync.cpp
//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, synchronous
//
//------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <thread>
#include "http_server.hpp"

// Handles an HTTP server connection
void
do_http_session(
    tcp::socket& socket,
    std::shared_ptr<std::string const> const& doc_root)
{
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<tcp::socket> lambda{socket, close, ec};

    for(;;)
    {
        // Read a request
        http::request<http::string_body> req;
        http::read(socket, buffer, req, ec);

        if(ec == http::error::end_of_stream)
            break;
        if(ec)
            return fail(ec, "read");

        // Send the response
        handle_request(*doc_root, std::move(req), lambda);
        if(ec)
            return fail(ec, "write");
        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            break;
        }
    }

    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string str_address("0.0.0.0");
    string str_doc_root("www");
    unsigned short port = 8080;

    if (argc == 4) {
        str_address = argv[1];
        port = atoi(argv[2]);
        str_doc_root = argv[3];
} else {
         cout <<
                "Usage: http_server [address] [port] [doc_root] \n" <<
                "Example:\n" <<
                "    http_server 0.0.0.0 8080 . "
        << endl;
}

    auto address = net::ip::make_address(str_address);
    auto doc_root = std::make_shared<std::string>(str_doc_root);

    cout << "address: " << address << endl;
    cout << "port: " << port << endl;
    cout << "doc_root: " << str_doc_root << endl;

    try
    {

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        cout << "listen: " << port << endl;

        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{std::bind(
                &do_http_session,
                std::move(socket),
                doc_root)}.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

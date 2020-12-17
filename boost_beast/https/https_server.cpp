/**
 * beast sample
 * 2020-07-01 K.OHWADA
 */

// HTTP SSL Server, synchronous

// g++ https/https_server.cpp -std=c++11 `pkg-config --cflags --libs boost`  `pkg-config --cflags --libs openssl` -o server

// original : https://github.com/boostorg/beast/blob/develop/example/http/server/sync-ssl/http_server_sync_ssl.cpp

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
// Example: HTTP SSL server, synchronous
//
//------------------------------------------------------------------------------


#include <iostream>
#include <string>
#include <thread>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>
#include "http_server.hpp"
#include "file_util.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


// Handles an HTTP SSL server connection
void
do_ssl_session(
    tcp::socket& socket,
    ssl::context& ctx,
    std::shared_ptr<std::string const> const& doc_root)
{
    bool close = false;
    beast::error_code ec;

    // Construct the stream around the socket
    beast::ssl_stream<tcp::socket&> stream{socket, ctx};

    // Perform the SSL handshake
    stream.handshake(ssl::stream_base::server, ec);
    if(ec)
        return fail(ec, "handshake");

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<beast::ssl_stream<tcp::socket&>> lambda{stream, close, ec};

    for(;;)
    {
        // Read a request
        http::request<http::string_body> req;
        http::read(stream, buffer, req, ec);
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

    // Perform the SSL shutdown
    stream.shutdown(ec);
    if(ec)
        return fail(ec, "shutdown");

    // At this point the connection is closed gracefully
}

//------------------------------------------------------------------------------


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

   const  string FILE_CERT("cert/localhost_cert.pem");
   const  string FILE_KEY("cert/localhost_key.pem");

    string str_address("0.0.0.0");
    string str_doc_root("www");
    unsigned short port = 8081;

    if (argc == 4) {
        str_address = argv[1];
        port = atoi(argv[2]);
        str_doc_root = argv[3];
} else {
         cout <<
                "Usage: https_server [address] [port] [doc_root] \n" <<
                "Example:\n" <<
                "    https_server 0.0.0.0 8081 . "
        << endl;
}

    auto address = net::ip::make_address(str_address);
    auto doc_root = std::make_shared<std::string>(str_doc_root);

    cout << "address: " << address << endl;
    cout << "port: " << port << endl;
    cout << "doc_root: " << str_doc_root << endl;

string cert;
string key;

    bool ret1 = readTextFile( FILE_CERT, cert );
    if(!ret1){
        cerr << "readTextFile failed: " << FILE_CERT << endl;
        return EXIT_FAILURE;
    }

    bool ret2 = readTextFile( FILE_KEY, key );
    if(!ret2){
        cerr << "readTextFile failed: " << FILE_KEY << endl;
        return EXIT_FAILURE;
    }

    try
    {
   
        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The SSL context is required, and holds certificates
        ssl::context ctx{ssl::context::tlsv12};

        // This holds the self-signed certificate used by the server
        // load_server_certificate(ctx);

    ctx.use_certificate_chain(
        boost::asio::buffer(cert.data(), cert.size()));

    ctx.use_private_key(
        boost::asio::buffer(key.data(), key.size()),
        boost::asio::ssl::context::file_format::pem);

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{std::bind(
                &do_ssl_session,
                std::move(socket),
                std::ref(ctx),
                doc_root)}.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

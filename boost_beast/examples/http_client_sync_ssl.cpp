/**
 * beast sample
 * 2020-07-01 K.OHWADA
 */

// HTTP SSL client, synchronous

// g++ http_client_sync_ssl.cpp -std=c++11 `pkg-config --cflags --libs boost`  `pkg-config --cflags --libs openssl`

// original : https://github.com/boostorg/beast/blob/develop/example/http/client/sync-ssl/http_client_sync_ssl.cpp
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
// Example: HTTP SSL client, synchronous
//
//------------------------------------------------------------------------------

#include "root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


using namespace std;


/**
 * main
 * Performs an HTTP GET and prints the response
 */
int main(int argc, char** argv)
{

    char *host = (char *)"www.example.com";

    string port("443");
    string target("/");
    char *arg4 = (char *)"1.1";

    bool is_verify = true;

    if(argc == 6) {
        host = argv[1];
        port = argv[2];
        target = argv[3];
        arg4 = argv[4];
       is_verify = (bool)stoi( argv[5] );
    } else if(argc == 5) {
        host = argv[1];
        port = argv[2];
        target = argv[3];
        arg4 = argv[4];
    } else if(argc == 4) {
        host = argv[1];
        port = argv[2];
        target = argv[3];
    } else if(argc == 2) {
        host = argv[1];
    } else {
        std::cout <<
            "Usage: " << argv[0] <<" [host] [port] [target] [HTTP version: 1.0 or 1.1(default)] [verify] \n" << endl;
    }
 
    int version = ( strcmp("1.0", arg4) == 0) ? 10 : 11;

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;
    cout << "target: " << target << endl;
    cout << "version: " << version << endl;
    cout << boolalpha << "verify: " << is_verify << endl;

    try
    {

        // The io_context is required for all I/O
        net::io_context ioc;

        // The SSL context is required, and holds certificates
        ssl::context ctx(ssl::context::tlsv12_client);

        // This holds the root certificate used for verification
        load_root_certificates(ctx);

        // Verify the remote server's certificate
if(is_verify){
        ctx.set_verify_mode(ssl::verify_peer);
}

            // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(stream.native_handle(), (char *)host) )
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the stream
        beast::error_code ec;
        stream.shutdown(ec);
        if(ec == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if(ec)
            throw beast::system_error{ec};

        // If we get here then the connection is closed gracefully
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * beast sample
 * 2020-07-01 K.OHWADA
 */

// HTTP client, synchronous

// original : https://github.com/boostorg/beast/blob/develop/example/http/client/sync/http_client_sync.cpp
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
// Example: HTTP client, synchronous
//
//------------------------------------------------------------------------------

//[example_http_client

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


using namespace std;


/**
 * main
 * Performs an HTTP GET and prints the response
 */
int main(int argc, char** argv)
{

    string host("www.example.com");
    string port("80");
    string target("/");
    char *arg4 = (char *)"1.1";

    if(argc == 5) {
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
            "Usage: " << argv[0] <<" [host] [port] [target] [HTTP version: 1.0 or 1.1(default)] \n" << endl;
    }
 
    int version = ( strcmp("1.0", arg4) == 0) ? 10 : 11;

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;
    cout << "target: " << target << endl;
    cout << "version: " << version << endl;


    try
    {

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);
   
        // Make the connection on the IP address we get from a lookup
        beast::error_code ec;
        stream.connect(results, ec);
        if(ec){
             throw beast::system_error{ec};
        }
        cout << "connect: " << host << " : " << port << endl;

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

        // Gracefully close the socket
        // beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if(ec && ec != beast::errc::not_connected)
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


// connect: www.example.com : 80
// HTTP/1.1 200 OK
// <title>Example Domain</title>



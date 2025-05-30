/**
 * beast sample
 * 2020-07-01 K.OHWADA
 */

// HTTP SSL client, coroutine

// g++ http_client_coro_ssl.cpp -std=c++11 `pkg-config --cflags --libs boost`  `pkg-config --cflags --libs openssl` -lboost_coroutine

// https://github.com/boostorg/beast/blob/develop/example/http/client/coro-ssl/http_client_coro_ssl.cpp
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
// Example: HTTP SSL client, coroutine
//
//------------------------------------------------------------------------------

#include "root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/spawn.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Performs an HTTP GET and prints the response
void
do_session(
    std::string const& host,
    std::string const& port,
    std::string const& target,
    int version,
    net::io_context& ioc,
    ssl::context& ctx,
    net::yield_context yield)
{
    beast::error_code ec;

    // These objects perform our I/O
    tcp::resolver resolver(ioc);
    beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if(! SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
    {
        ec.assign(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << ec.message() << "\n";
        return;
    }

    // Look up the domain name
    auto const results = resolver.async_resolve(host, port, yield[ec]);
    if(ec)
        return fail(ec, "resolve");

    // Set the timeout.
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // Make the connection on the IP address we get from a lookup
    get_lowest_layer(stream).async_connect(results, yield[ec]);
    if(ec)
        return fail(ec, "connect");

    // Set the timeout.
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // Perform the SSL handshake
    stream.async_handshake(ssl::stream_base::client, yield[ec]);
    if(ec)
        return fail(ec, "handshake");

    // Set up an HTTP GET request message
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Set the timeout.
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // Send the HTTP request to the remote host
    http::async_write(stream, req, yield[ec]);
    if(ec)
        return fail(ec, "write");

    // This buffer is used for reading and must be persisted
    beast::flat_buffer b;

    // Declare a container to hold the response
    http::response<http::dynamic_body> res;

    // Receive the HTTP response
    http::async_read(stream, b, res, yield[ec]);
    if(ec)
        return fail(ec, "read");

    // Write the message to standard out
    std::cout << res << std::endl;

    // Set the timeout.
    beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

    // Gracefully close the stream
    stream.async_shutdown(yield[ec]);
    if(ec == net::error::eof)
    {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if(ec)
        return fail(ec, "shutdown");

    // If we get here then the connection is closed gracefully
}

//------------------------------------------------------------------------------


using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    string host("www.example.com");
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


    // The io_context is required for all I/O
    net::io_context ioc;

    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};

    // This holds the root certificate used for verification
    load_root_certificates(ctx);

    // Verify the remote server's certificate
    if(is_verify){
        ctx.set_verify_mode(ssl::verify_peer);
    }

    // Launch the asynchronous operation
    boost::asio::spawn(ioc, std::bind(
        &do_session,
        std::string(host),
        std::string(port),
        std::string(target),
        version,
        std::ref(ioc),
        std::ref(ctx),
        std::placeholders::_1));

    // Run the I/O service. The call will return when
    // the get operation is complete.
    ioc.run();

    return EXIT_SUCCESS;
}

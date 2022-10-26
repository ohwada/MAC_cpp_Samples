#pragma once
/**
 * http_server.hpp
 * 2022-06-01 K.OHWADA
 */

// Example: HTTP server, synchronous
// original : https://github.com/boostorg/beast/blob/develop/example/http/server/sync/http_server_sync.cpp


#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include "response_builder.hpp"
#include "msg_builder.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


// prototype
bool run_server(boost::asio::ip::port_type port, std::string doc_root="." );
void do_http_session(
    tcp::socket& socket,
    std::shared_ptr<std::string const> const& doc_root);
std::string
path_cat(
    beast::string_view base,
    beast::string_view path);
void fail(beast::error_code ec, char const* what);


template<
    class Body, class Allocator,
    class Send>
void handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send);


// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
template<class Stream>
struct send_lambda
{
    Stream& stream_;
    bool& close_;
    beast::error_code& ec_;

    explicit
    send_lambda(
        Stream& stream,
        bool& close,
        beast::error_code& ec)
        : stream_(stream)
        , close_(close)
        , ec_(ec)
    {
    }


/**
 * operator
 */
    template<bool isRequest, class Body, class Fields>
    void
    operator()(http::message<isRequest, Body, Fields>&& msg) const
    {
        // Determine if we should close the connection after
        close_ = msg.need_eof();

        // We need the serializer here because the serializer requires
        // a non-const file_body, and the message oriented version of
        // http::write only works with const messages.
        http::serializer<isRequest, Body, Fields> sr{msg};
        http::write(stream_, sr, ec_);
    }
};



/**
 * run_server
 */
bool run_server(boost::asio::ip::port_type port, std::string str_doc_root)
{
    std::string str_address("0.0.0.0");

    auto address = net::ip::make_address(str_address);
    
    auto doc_root = std::make_shared<std::string>(str_doc_root);

    try
    {

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        std::cout << "listen: " << port << std::endl;

        while(true)
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

        } // while
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}


/**
 *  do_http_session
 */
// Handles an HTTP server connection
void do_http_session(
    tcp::socket& socket,
    std::shared_ptr<std::string const> const& doc_root)
{
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    send_lambda<tcp::socket> lambda{socket, close, ec};

    while(true)
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
    } // while

    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}


/**
 *  failReport a failure
 * Report a failure
 */
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}


/**
 * path_cat
 * Append an HTTP rel-path to a local filesystem path.
 * The returned path is normalized for the platform.
 */
std::string
path_cat(
    beast::string_view base,
    beast::string_view path)
{
	if (base.empty())
		return std::string(path);
    std::string result(base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for(auto& c : result)
        if(c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
}


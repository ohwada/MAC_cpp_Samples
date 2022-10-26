/**
 * http_client.hpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Client, synchronous

// original : https://github.com/boostorg/beast/blob/develop/example/http/client/sync/http_client_sync.cpp


#include <iostream>
#include <sstream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

const std::string CONTENT_TYPE_FORM("application/x-www-form-urlencoded");

const std::string CONTENT_TYPE_JSON("application/json; charset=utf-8");

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>

// prototype
http::request<http::string_body>
build_http_get_request(std::string host, std::string target );
http::request<http::string_body>
build_http_post_request(std::string host, std::string target, std::string postdata, std::string content_type );
bool http_client(std::string host, int port, http::request<http::string_body> req, std::string &response, std::string &error);
bool split_header_body(std::string text, std::string &header, std::string &body);


namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>


/**
 *  build_http_get_request
 */
http::request<http::string_body>
build_http_get_request(std::string host, std::string target )
{
    unsigned HTTP_VERSION = 11;

    // Set up an HTTP GET request message
    http::request<http::string_body> 
    req{http::verb::get, target, HTTP_VERSION};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    return req;
}


/**
 *  build_http_post_request
 */
http::request<http::string_body>
build_http_post_request(std::string host, std::string target, std::string postdata, std::string content_type )
{
    unsigned HTTP_VERSION = 11;

    // Set up an HTTP GET request message
    http::request<http::string_body> 
    req{http::verb::post, target, HTTP_VERSION};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, content_type);
        req.body() = postdata;
        req.prepare_payload();
    return req;
}


/**
 *  http_client
 */
bool http_client(std::string host, int port, http::request<http::string_body> req, std::string &response, std::string &error)
{

    try
    {

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, std::to_string(port) );

        // Make the connection on the IP address we get from a lookup
        beast::error_code ec;
        stream.connect(results, ec);
        if(ec){
             throw beast::system_error{ec};
        }
        std::cout << "connect: " << host << " : " << port << std::endl;

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        // std::cout << res << std::endl;

// TODO:
// get omly body
        std::ostringstream oss;
        oss <<  res;
        response = oss.str();

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
        error = e.what();
        std::cerr << "Error: " << e.what() << std::endl;
        error = e.what();
        return false;
    }

    return true;
}


/*
 *  split_header_body
*/
bool split_header_body(std::string text, std::string &header, std::string &body)
{

    const std::string find_word("\r\n\r\n"); 


    auto pos = text.find( find_word);
    
    if(pos == std::string::npos) {
        return false;
    }

    header = text.substr(0, pos);
    body = text.substr(pos+4);

    return true;
}

/**
 * http_file_server.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Server, synchronous
// file server  
// return the requested file content

// original : https://github.com/boostorg/beast/blob/develop/example/http/server/sync/http_server_sync.cpp

// Note
// HEAD mtheod
// curl -v -I locsalhost:8080

#include <iostream>
#include <string>
#include <thread>
#include "http_server.hpp"


// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.

template<
    class Body, class Allocator,
    class Send>
void
handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send)
{

    std::cout << std::endl;
    std::cout << "request" << std::endl;
    std::cout << req.base() << std::endl;

    // Returns a bad request response
    auto const bad_request =
    [](beast::string_view why)
    {
        auto text = std::string(why);
        beast::string_view mime("text/html");

        return build_response_bad_request(text,  mime);
    };

    // Returns a not found response
    auto const not_found =
    [](beast::string_view target)
    {
        auto text = build_msg_not_found( std::string(target) );
        beast::string_view mime("text/html");

        auto res = build_not_found_response(text, mime);

        std::cout << std::endl;
        std::cout << "response" << std::endl;
        std::cout << res.base() << std::endl;

        return res;
    };

    // Returns a server error response
    auto const server_error =
    [](beast::string_view what)
    {
        auto text = build_msg_server_error( std::string(what) );
        beast::string_view mime("text/html");
        return build_response_internal_server_error( text,  mime);
    };


    // Make sure we can handle the method
    if( req.method() != http::verb::get &&
        req.method() != http::verb::head)
        return send(bad_request("Unknown HTTP-method"));


    // Request path must be absolute and not contain "..".
    if( req.target().empty() ||
        req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return send(bad_request("Illegal request-target"));


    // Build the path to the requested file
    std::string path = path_cat(doc_root, req.target());
    if(req.target().back() == '/')
        path.append("index.html");


    // Attempt to open the file
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if(ec == beast::errc::no_such_file_or_directory)
        return send(not_found(req.target()));

    // Handle an unknown error
    if(ec)
        return send(server_error(ec.message()));

    // Respond to HEAD request
    if(req.method() == http::verb::head)
    {
        auto res = build_response_empty_body(path);
        send(std::move(res));
        std::cout << std::endl;
        std::cout << "head response" << std::endl;
        std::cout << res.base() << std::endl;
        return;
    }


    // Respond to GET request
    auto res = build_file_response(path);
    send(std::move(res));
    std::cout << std::endl;
    std::cout << "get response" << std::endl;
    std::cout << res.base() << std::endl;
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    boost::asio::ip::port_type port = 8080;

    string doc_root("www");


   if (argc == 3) {
        port = atoi(argv[2]);
        doc_root = argv[3];
    } else if (argc == 2) {
        port = atoi(argv[2]);
    } else {
         cout << "Usage: " << argv[0] << " [port] [doc_root]" << endl;
    }
    
    run_server(port, doc_root);

    return 0;
}

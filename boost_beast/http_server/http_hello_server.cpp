/**
 * http_hello_server.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Server, synchronous
// return "Hello World"  

// original : https://github.com/boostorg/beast/blob/develop/example/http/server/sync/http_server_sync.cpp

#include <iostream>
#include <string>
#include "http_server.hpp"


/**
 * handle_request
 */
template<
    class Body, class Allocator,
    class Send>
void handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send)
{
  
std::cout << std::endl;
std::cout << "request" << std::endl;
std::cout << req.base() << std::endl;

    std::string body("Hello World");
    beast::string_view mime("text/plain");

    auto res = build_string_response(body,  mime);
    send(std::move(res));

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << res.base() << std::endl;
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    boost::asio::ip::port_type port = 8080;

    if (argc == 2) {
        port = atoi(argv[2]);
    } else {
         cout << "Usage: " << argv[0] << " [port]" << endl;
    }

    run_server(port);

    return 0;
}

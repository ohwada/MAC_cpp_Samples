/**
 * http_get_form_server.cpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include "http_server.hpp"
#include "http_form_server.hpp"


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

std::string method( req.method_string() );
std::string target( req.target() );

std::cout << "method" << std::endl;
std::cout << method << std::endl;

std::cout << "target" << std::endl;
std::cout << target << std::endl;

    beast::string_view mime("text/html");

    std::string html;

bool ret = build_form_response(method, target, html);
if(ret)
{
    std::cout << "html" << std::endl;
    std::cout << html << std::endl;

    auto res = build_string_response(html, mime);
    send(std::move(res));

        std::cout << std::endl;
        std::cout << "response" << std::endl;
        std::cout << res.base() << std::endl;

        return;
}

    std::string path("data/index_get.html");

    auto res = build_file_response(path);
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

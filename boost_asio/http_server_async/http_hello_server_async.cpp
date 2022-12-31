/**
 *  http_hello_server_async.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include "async_server.hpp"
#include "response_builder.hpp"


/**
 *  do_handle_read
 */
   std::string do_handle_read(std::string doc_root, std::string read_data)
{
    std::cout << "request" << std::endl;
    std::cout << read_data << std::endl;

    std::string text("Hello World");
    std::string mime("text/plain");

    auto response = 
    build_response_text(text, mime);

    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    return response;
}


/**
 *  main
 */
int main(int argc, char* argv[])
{

    unsigned short port = 8080;

    std::string doc_root;

    if (argc == 2){
        port = std::atoi(argv[1]);
    } else {
      std::cerr << "Usage: http_server <port>\n";
    }

    run_server(port, doc_root);
 
  return 0;
}

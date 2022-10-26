/**
 * http_hello_server.cpp
 * 2022-06-01 K.OHWADA
 */

// return fixed prepared response "Hello World"

#include <iostream>
#include <string>
#include "http_server.hpp"
#include "response_builer.hpp"


/**
 *  on_accept
 */
void on_accept(tcp::socket socket_client )
{
    std::string request;
    std::string error;

    bool ret1 =  asio_read_until_lf(socket_client, request, error);
    if(!ret1){
        std::cerr << "asio read: " << error << std::endl;
    }

    std::cout << "request" << std::endl;
    std::cout << request << std::endl;

    std::string body("Hello World");
    std::string mime("text/plain");

    std::string response = 
    build_response_ok(body, mime);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    bool ret2 = asio_write(socket_client, response, error);
        if(!ret2) {
        std::cerr << "asio write: " << error << std::endl;
    }

}


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    int port = 8080;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        cerr << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port);

return EXIT_SUCCESS;

}

 
// listen port: 8080


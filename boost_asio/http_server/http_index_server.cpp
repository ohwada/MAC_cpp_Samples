/**
 * http_index_server.cpp
 * 2022-06-01 K.OHWADA
 */

// return fixed prepared response index.html


#include <iostream>
#include <string>
#include "http_server.hpp"
#include "response_builer.hpp"
#include "file_util.hpp"


/**
 * get_index_html
 */
bool get_index_html(std::string &text)
{
    std::string file("data/index.html");
    return readTextFile(file, text);
}


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
 
    std::string text;
    bool ret2 = get_index_html(text);
    if(!ret2){
        std::cerr << "cannot read index.html" << std::endl;
    }

    std::string mime("text/html");

    std::string response = 
    build_response_ok(text, mime);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    bool ret3 = asio_write(socket_client, response, error);
        if(!ret3) {
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


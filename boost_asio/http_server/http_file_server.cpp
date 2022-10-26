/**
 * simple_http_file_server.cpp
 * 2022-06-01 K.OHWADA
 */


// file server
// return the requested file content


#include <iostream>
#include <string>
#include "http_file_server.hpp"
#include "http_server.hpp"
#include "request_parser.hpp"
#include "not_found_builder.hpp"


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

    std::cout << std::endl;
    std::cout << "request" << std::endl;
    std::cout << request << std::endl;

    std::string path;

    bool ret2 = parse_request(request,  path);
    if(!ret2){
        std::cerr << "cannot parseRequest " << std::endl;
    }

       std::cout << path << std::endl;

    std::string file = get_file(path);
    std::cout << file << std::endl;

    std::string response_header;
    std::string response;

    if( existsFile(file) )
    {
        std::string data = read_file(file);
        std::string mime = get_mime(file);
        std::cout << mime << std::endl;
        response_header = 
        build_response_header_ok(data, mime);
        response =
        build_response(response_header, data);
    } else {
        std::string msg = build_msg_not_found(path);
        response_header = 
        get_response_header_not_found(msg);
        response =
        build_response(response_header, msg);
    }

    std::cout << std::endl;
    std::cout << "response header" << std::endl;
    std::cout << response_header << std::endl;

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


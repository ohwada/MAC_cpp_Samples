/**
 * http_server.hpp
 * 2020-07-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

#include <iostream>
#include <string>
#include "asio_socket.hpp"
#include "file_util.hpp"


// prototype
void http_server(int port, std::string response);
bool get_index_html(std::string &text);
std::string build_response(std::string html);

using namespace boost::asio;
using ip::tcp;



/**
 * http_server
 */
void http_server(int port, std::string response)
{

  boost::asio::io_service io_service;

  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port ) );
  
 std::cout << "listen port: " << port << std::endl;

while(1)
{
  tcp::socket socket_client(io_service);

    try{
        acceptor.accept(socket_client);
    } catch ( boost::system::system_error &err ){
        std::cerr << "accept: " << err.what() << std::endl;
    }


    std::string read_data;
    std::string error;


    bool ret1 =  asio_read_until_lf(socket_client, read_data, error);
    if(ret1){
        std::cout << read_data << std::endl;
    } else {
        std::cerr << "read: " << error << std::endl;
    }

    std::string write_data( response );

     bool ret2 = asio_write(socket_client, write_data, error);
        if(!ret2) {
        std::cerr << "write: " << error << std::endl;
    }

        // std::cout <<  write_data << std::endl;

    } // while

}


/**
 * get_index_html
 */
bool get_index_html(std::string &text)
{
    std::string file("data/index.html");
    return readTextFile(file, text);
}


/**
 *  build_response
 */
std::string build_response(std::string html)
{

    const std::string CRLF("\r\n");

 const std::string HEADER_OK("HTTP/1.1 200 OK\r\n");
    const std::string HEADER_CONTENT_HTML("Content-Type: text/html\r\n");

    const std::string HEADER_CONTENT_LENGTH("Content-Length: ");

    const std::string CLOSE("Connection: Close\r\n");

    std::string content_length = 
    HEADER_CONTENT_LENGTH 
    +std::to_string( html.size() )
    + CRLF;

    std::string response = 
    HEADER_OK
    + HEADER_CONTENT_HTML
    +  content_length
    + CRLF
    + html;

    return response;
}



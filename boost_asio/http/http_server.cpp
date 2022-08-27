/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTP Server
// return fixed prepared response

// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

// g++ http_server.cpp -std=c++11 `pkg-config --cflags --libs boost` -o server

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "asio_socket.hpp"
#include "http_server.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::cerr;
using std::endl;


/**
 * main
 */
int main(int argc, char *argv[])
{

    const char TITLE[] = "HTTP Server demo";

    const char HEADLINE[] = "boost/asio HTTP Server demo";


    int port = 8080;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        cerr << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;

// build response
    char html[1024];
    char response[1024];

    build_html( (char *)TITLE, (char *)HEADLINE, (char *)html );

    build_response( (char *)html, (char *)response);

    printf("%s \n", response);


  boost::asio::io_service io_service;

  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port ) );
  
 cout << "listen port: " << port << endl;

  tcp::socket socket_client(io_service);

    try{
        acceptor.accept(socket_client);
    } catch ( boost::system::system_error &err ){
        cerr << "accept: " << err.what() << endl;
        return EXIT_FAILURE;
    }

    cout << "accept" << endl;


    string read_data;
    string error;


    bool ret1 =  asio_read_until_lf(socket_client, read_data, error);
    if(ret1){
        cout << read_data << endl;
    } else {
        cerr << "read: " << error << endl;
        return EXIT_FAILURE;
    }

    string write_data( response );

     bool ret2 = asio_write(socket_client, write_data, error);
        if(!ret2) {
        cerr << "write: " << error << endl;
        return EXIT_FAILURE;
    }

return EXIT_SUCCESS;

}

 
// listen port: 8080


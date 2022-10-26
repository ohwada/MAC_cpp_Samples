#pragma once
/**
 * http_server.hpp
 */

// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

#include <iostream>
#include <string>
#include "asio_socket.hpp"

using namespace boost::asio;
using ip::tcp;


// prototype
void run_server(int port);
 void on_accept(tcp::socket socket_client );


/**
 * run_server
 */
void run_server(int port)
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

    on_accept( std::move(socket_client) );

    } // while

}


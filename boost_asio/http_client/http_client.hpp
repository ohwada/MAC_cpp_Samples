#pragma once
/**
 * http_client.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include <boost/format.hpp>
#include "asio_socket.hpp"
#include "resolver.hpp"

// constant
const uint16_t PORT_HTTP = 80;

const std::string ROOT_PATH("/");


// prototype
bool http_client(std::string host, int port, std::string request, std::string &response);
bool localhost_client(int port, std::string request, std::string &response);
std::string build_http_root_path_request(std::string host);
std::string build_http_request(std::string host, std::string path);
bool split_header_body(std::string text, std::string &header, std::string &body);


using namespace boost::asio;
using ip::tcp;


/**
 * http_client
 */
bool http_client(std::string host, int port, std::string request, std::string &response)
{
    boost::asio::ip::address address;
    std::string error;

bool ret1 = get_address( host, address, error );

    if(!ret1){
        std::cerr << "get_address: " << error << std::endl;
        return false;
    }

    auto str_ipaddr = address.to_string();

    std::cout << "ip address: " << str_ipaddr << std::endl;

    tcp::endpoint endpoint(address, port );

    boost::asio::io_service io_service;
    tcp::socket socket(io_service);

    try {
        socket.connect( endpoint );
   } catch ( boost::system::system_error &err ) {
        std::cerr << "connect: " << err.what() << std::endl;
            return false;
    }

    std::cout << "connect: " << host << " : "<< port << std::endl;

    std::string write_data( request );

    bool ret2 = asio_write(socket, write_data, error );
    if( !ret2 ) {
        std::cerr << "write: " << error << std::endl;
        return false;
    }

    std::string read_data;

    bool ret3 = asio_read(socket, read_data, error);
    if( !ret3 ) {
        std::cerr << "read: " << error << std::endl;
        return false;
    }

    response = read_data;

  return true;

}


/**
 * localhost_client
 */
bool localhost_client(int port, std::string request, std::string &response)
{
    const std::string IPADDR("127.0.0.1");

    std::string host("localhost");

    boost::asio::ip::address address = boost::asio::ip::address::from_string( IPADDR );

   // boost::asio::ip::address address;
    // bool ret1 = get_address( host, address, error );

    tcp::endpoint endpoint(address, port );

    boost::asio::io_service io_service;
    tcp::socket socket(io_service);

    try {
        socket.connect( endpoint );
   } catch ( boost::system::system_error &err ) {
        std::cerr << "connect: " << err.what() << std::endl;
            return false;
    }

    std::cout << "connect: " << host << " : "<< port << std::endl;

    std::string write_data( request );

    std::string error;

    bool ret2 = asio_write(socket, write_data, error );
    if( !ret2 ) {
        std::cerr << "asio write: " << error << std::endl;
        return false;
    }


    std::string read_data;

    // bool ret3 = asio_read(socket, read_data, error);
    bool ret3 =  asio_read_until_lf(socket, read_data, error);

    if( !ret3 ) {
        std::cerr << "read: " << error << std::endl;
        return false;
    }


    response = read_data;

  return true;

}


/** 
 *  build_http_root_path_request
 */
std::string build_http_root_path_request(std::string host)
{
    return build_http_request( host, ROOT_PATH);
}


/** 
 *  build_http_request
 */
std::string build_http_request(std::string host, std::string path)
{

    const std::string HEADER_ACCEPT_ALL("Accept: */* \r\n");

    const std::string HEADER_CLOSE("Connection: close\r\n\r\n");

// Dont put space after HTTP/1.1 
    const std::string FORMAT_GET("GET %s HTTP/1.1\r\n");

    const std::string FORMAT_HOST("Host: %s\r\n");

    std::string hdr_get =
    boost::str( boost::format( FORMAT_GET) % path );

    std::string hdr_host =
    boost::str( boost::format( FORMAT_HOST) % host );

    std::string request = hdr_get
    + HEADER_ACCEPT_ALL
    + hdr_host
    + HEADER_CLOSE;

    return request;
}


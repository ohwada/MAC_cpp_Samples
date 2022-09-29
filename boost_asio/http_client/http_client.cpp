/**
 * http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Client
// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

// g++ http_client.cpp -std=c++11 `pkg-config --cflags --libs boost` -o bin/client


#include <iostream>
#include <boost/asio.hpp>
#include "asio_socket.hpp"
#include "resolver.hpp"
#include "http_client.hpp"


using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::cerr;
using std::endl;



bool client(std::string host, int port, std::string request, std::string &response)
{

    boost::asio::ip::address address;
    std::string error;

bool ret1 = get_address( host, address, error );

    if(!ret1){
        std::cerr << "get_address: " << error << std::endl;
        return false;
    }


    std::string ipaddr = address.to_string();

    std::cout << "ip address: " << ipaddr << std::endl;

    tcp::endpoint endpoint(address, port );

    boost::asio::io_service io_service;
    tcp::socket socket(io_service);

    try {
        socket.connect( endpoint );
   } catch ( boost::system::system_error &err ) {
        cerr << "connect: " << err.what() << endl;
            return false;
    }

    std::cout << "connect: " << host << " : "<< port << std::endl;

    string write_data( request );

    bool ret2 = asio_write(socket, write_data, error );

    if( !ret2 ) {
        std::cerr << "write: " << error << std::endl;
        return false;
    }

    string read_data;

    bool ret3 = asio_read(socket, read_data, error);

    if( !ret3 ) {
        std::cerr << "read: " << error << std::endl;
        return false;
    }

    response = read_data;

  return true;

}



/**
 * main
 */
int main(int argc, char *argv[])
{

    std::string host("example.com");

    int port = PORT_HTTP;

    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    string request =
    build_http_root_path_request( host);

    cout << endl;
    cout << "request" << endl;
    cout << request << endl;

    string response;
    client(host, port, request, response);

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    return 0;
}
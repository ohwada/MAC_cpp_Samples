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
        cerr << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cerr << "host: " << host << endl;
    cerr << "port: " << port << endl;

    string request;

    build_http_root_path_request( host, request );

    cout << "request" << endl;
    cout << request << endl;

    boost::asio::ip::address address;
    std::string error;

bool ret1 = get_address( host, address, error );

    if(!ret1){
        cerr << "get_address: " << error << endl;
        return EXIT_FAILURE;
    }


    string ipaddr = address.to_string();

    cout << "ip address: " << ipaddr << endl;

    tcp::endpoint endpoint(address, port );

    boost::asio::io_service io_service;
    tcp::socket socket(io_service);

    try {
        socket.connect( endpoint );
   } catch ( boost::system::system_error &err ) {
        cerr << "connect: " << err.what() << endl;
            return EXIT_FAILURE;
    }

    cout << "connect: " << host << " : "<< port << endl;

    

    string write_data( request );

    bool ret2 = asio_write(socket, write_data, error );

    if( !ret2 ) {
        cerr << "write: " << error << endl;
        return EXIT_FAILURE;
    }

    string read_data;

    bool ret3 = asio_read(socket, read_data, error);

    if( !ret3 ) {
        cerr << "read: " << error << endl;
        return EXIT_FAILURE;
    }

    cout << "response" << endl;
    cout << read_data << endl;

  return EXIT_SUCCESS;

}

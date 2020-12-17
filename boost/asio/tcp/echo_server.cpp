/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// TCP Echo Server
// Echo back the received data as it is

// https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T


#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "asio_socket.hpp"
#include "echo_port.h"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::cerr;
using std::endl;


/**
 * main
 */
int main(void) 
{

  boost::asio::io_service io_service;

  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT ) );
  
 cout << "listen port: " << PORT << endl;

  tcp::socket socket_client(io_service);

    try{
        acceptor.accept(socket_client);
    } catch ( boost::system::system_error &err ){
        cerr << "accept: " << err.what() << endl;
        return EXIT_FAILURE;
    }

    cout << "accept" << endl;

    string read_data;
    string write_data;
    string error;

    bool is_error = false;

while(1)
{

  bool ret1 =  asio_read_until_lf(socket_client, read_data, error);
    if(ret1){
        cout << "r: " << read_data;
    } else {
        cout << "read: " << error << endl;
        is_error = true;
        break;
    }

// echo back
    write_data = read_data;

     bool ret2 = asio_write_with_lf(socket_client, write_data, error);
        if(ret2) {
        // cout << "s: " << write_data;
    } else {
        cout << "write: " << error << endl;
        is_error = true;
        break;
    }

    cout << endl;

} // while

if (is_error){
    cout << "failed" << endl;
    return EXIT_FAILURE;
}

    cout << "successful" << endl;

    return EXIT_SUCCESS;

}


// listen port: 1234


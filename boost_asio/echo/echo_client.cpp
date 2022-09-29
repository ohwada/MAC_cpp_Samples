/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// TCP Client for Echo server
// send TCP packet continuously every one second

// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

// g++ echo_client.cpp -std=c++11 `pkg-config --cflags --libs boost` -o client

#include <iostream>
#include <thread>
#include <chrono>

#include <boost/format.hpp>
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

    const std::string IPADDR("127.0.0.1");

    const int port = PORT;

    const int MAX_LOOP = 100;

    const long SLEEP = 1000; // 1 sec

  boost::asio::io_service io_service;
  tcp::socket socket(io_service);

    tcp::endpoint endpoint( boost::asio::ip::address::from_string (  IPADDR ), PORT );

    try {
        socket.connect( endpoint );
   } catch ( boost::system::system_error &err ) {
        cerr << "connect: " << err.what() << endl;
            return EXIT_FAILURE;
    }

    cout << "connect: " << IPADDR << " : "<< port << endl;

    string  write_data;
    string  read_data;
    string  error;

    bool is_error = false;

for(int i=0; i < MAX_LOOP; i++)
{
    write_data = boost::str( boost::format("%03d") % i ) ;

    bool ret2 = asio_write_with_lf(socket, write_data, error );

  if( ret2 ) {
    cout << "s: " << write_data << endl;
  } else {
    cerr << "write: " << error << endl;
    is_error = true;
    break;
  }

    bool ret3 = asio_read_until_lf(socket, read_data, error);

    if( ret3 ) {
        cout << "r: " << read_data;
    } else {
        cerr << "read: " << error << endl;
        is_error = true;
        break;
  }

std::this_thread::sleep_for(std::chrono:: milliseconds (SLEEP));

} // for

if (is_error){
    cout << "failed" << endl;
    return EXIT_FAILURE;
}

    cout << "successful" << endl;
  return EXIT_SUCCESS;

}

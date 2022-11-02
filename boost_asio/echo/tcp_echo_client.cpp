/**
 * tcp_echo_client.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/blocking_tcp_echo_client.cpp


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include "port.h"

    using namespace std; 
using boost::asio::ip::tcp;

enum { max_length = 1024 };

void echo_client(std::string host, std::string port)
{

    const int MAX_LOOP = 100;
    const long SLEEP = 1000; // 1 sec

  try
  {
 
    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(tcp::v4(), host, port);

    tcp::socket s(io_context);
    boost::asio::connect(s, endpoints);

    char reply[max_length];

for(int i=0; i < MAX_LOOP; i++)
{
    std::string request = boost::str( boost::format("%03d") % i ) ;
    size_t request_length = request.length();

    boost::asio::write(s, boost::asio::buffer(request));

    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, request_length));

    std::cout << "r: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono:: milliseconds (SLEEP));
} // for

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}


/**
 * main
 */
int main(int argc, char* argv[])
{

    string host("localhost");
    
    string port = to_string(PORT);


    if(argc == 3) {
      	host = argv[1];
      	port = argv[2];
    } else {
        cout << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    echo_client(host, port);

  return 0;
}

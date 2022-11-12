/**
 * udp_echo_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/chriskohlhoff/asio/blob/master/asio/src/examples/cpp03/echo/blocking_udp_echo_server.cpp


#include <cstdlib>
#include <iostream>
#include "asio.hpp"
#include "port.h"

using asio::ip::udp;

enum { max_length = 1024 };


/**
 * server
 */
void server(asio::io_context& io_context, unsigned short port)
{
  udp::socket sock(io_context, udp::endpoint(udp::v4(), port));
    std::cout << "listen port: " << port << std::endl;
  while(1)
  {
    char data[max_length];
    udp::endpoint sender_endpoint;
    size_t length = sock.receive_from(
        asio::buffer(data, max_length), sender_endpoint);
    std::cout << "r: " << data << std::endl;
    sock.send_to(asio::buffer(data, length), sender_endpoint);
  } // while
}


/**
 * run_server
 */
bool run_server(unsigned short port)
{
  try
  {
    asio::io_context io_context;

    using namespace std; // For atoi.
    server(io_context, port);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return false;
  }

    return true;
}

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    unsigned short port = PORT;

    if(argc == 2) {
      	port = atoi(argv[1]);
    } else {
        cout << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port);

  return 0;
}

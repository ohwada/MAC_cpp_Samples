/**
 * tcp_echo_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/blocking_tcp_echo_server.cpp


#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "port.h"

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;


/**
 * session
 */
void session(socket_ptr sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock->read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

        std::cout << "r: ";
        std::cout.write(data, length);
        std::cout << std::endl;


      boost::asio::write(*sock, boost::asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}


/**
 * server
 */
void server(boost::asio::io_context& io_context, unsigned short port)
{
  tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));

    std::cout << "listen port: " << port << std::endl;

  for (;;)
  {
    socket_ptr sock(new tcp::socket(io_context));
    a.accept(*sock);
    boost::thread t(boost::bind(session, sock));
  }
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

  try
  {
    boost::asio::io_context io_context;

    server(io_context, port);
  }
  catch (std::exception& e)
  {
    cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

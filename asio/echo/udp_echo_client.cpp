/**
 * udp_echo_client.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/chriskohlhoff/asio/blob/master/asio/src/examples/cpp03/echo/blocking_udp_echo_client.cpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include <chrono>
#include "asio.hpp"
#include "port.h"

using asio::ip::udp;

enum { max_length = 1024 };



/**
 * run_client
 */
bool run_client(std::string host, std::string port)
{

    int MAX_LOOP = 100;
    const long SLEEP = 1000; // 1 sec

    using namespace std; // For strlen.

  try
  {

    asio::io_context io_context;

    udp::socket s(io_context, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_context);
    udp::resolver::results_type endpoints =
      resolver.resolve(udp::v4(), host, port);

    char request[max_length];

    for(int i=0; i<MAX_LOOP; i++)
{
    snprintf(request, max_length, "%03d", i);
   
    size_t request_length = strlen(request);

    s.send_to(asio::buffer(request, request_length), *endpoints.begin());

    char reply[max_length];
    udp::endpoint sender_endpoint;
    size_t reply_length = s.receive_from(
        asio::buffer(reply, max_length), sender_endpoint);
    std::cout << "r: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono:: milliseconds (SLEEP));
} // while

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

    std::string port = std::to_string(PORT);

    if(argc == 2) {
      	port = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;


    std::string host("localhost");

    run_client(host, port);

  return 0;
}

/**
 *  client.cpp
 * 2022-06-01 K.OHWADA
 */

// Client-server Fizz-Buzz : Client
// original: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_96c/main.cpp

#include <iostream>
#include <string>
#include <array>

#define ASIO_STANDALONE
#include "boost/asio.hpp"

#include "config.h"


/**
 *  run_client
 */
void run_client(std::string host, short const port)
{
    const int MAX = 100;
    const int SLEEP = 1000; // 1 sec

   try
   {
      boost::asio::io_context context;
       boost::asio::ip::tcp::socket tcp_socket(context);
       boost::asio::ip::tcp::resolver resolver(context);
       boost::asio::connect(tcp_socket, 
                    resolver.resolve({ host.data(), std::to_string(port) }));


      for(int i=1; i<MAX; i++)
      {
         std::cout << "< " << i << std::endl;;

         auto request = std::to_string(i);
         tcp_socket.write_some(boost::asio::buffer(request, request.length()));

         std::array<char, 1024> reply;
         auto reply_length = tcp_socket.read_some(boost::asio::buffer(reply, reply.size()));

         std::cout << "> ";
         std::cout.write(reply.data(), reply_length);
         std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));  

      } // for

   }
   catch (std::exception const & e)
   {
      std::cerr << "exception: " << e.what() << std::endl;
   }
}


/**
 *  main
 */
int main()
{
    const std::string HOST("localhost");

   run_client(HOST, PORT);

    return 0;
}


// < 3
// > fizz
// < 4
// > 4
// < 5
// > buzz


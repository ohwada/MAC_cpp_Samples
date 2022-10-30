/**
 * server.cpp
 * 2022-06-01 K.OHWADA
 */

// Client-server Fizz-Buzz : Server
// refrence: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_96s/main.cpp


#include <iostream>
#include "tcp_server.hpp"
#include "port.h"


/**
 *  fizzbuzz
 */
std::string fizzbuzz(int const number)
{
   if (number != 0)
   {
      auto m3 = number % 3;
      auto m5 = number % 5;
      if (m3 == 0 && m5 == 0) return "fizzbuzz";
      else if (m5 == 0) return "buzz";
      else if (m3 == 0) return "fizz";
   }

   return std::to_string(number);
}


/**
 *  on_connect
 */
void on_connect(Poco::Net::StreamSocket *ss)
{
      while (true) {
            auto str = tcp_read(*ss);
            std::cout << "rcv: " << str << std::endl;
            auto result = fizzbuzz(std::atoi(str.c_str()));
            tcp_send(*ss, result);
        } // while
}


/**
 * main
 */
int main() 
{

    run_server(PORT);

    return 0;
}

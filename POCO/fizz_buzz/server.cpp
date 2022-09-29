/**
 * server.cpp
 * 2022-06-01 K.OHWADA
 */

// Client-server Fizz-Buzz : Server
// refrence: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_96s/main.cpp


#include <iostream>

#include <Poco/Net/Socket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>

#include "pico_tcp.hpp"
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
 * main
 */
int main() 
{

    while (true) {
        Poco::Net::ServerSocket *serv;
        Poco::Net::StreamSocket *ss;
        serv = new Poco::Net::ServerSocket(PORT);
        serv->listen();

        std::cout << "listen port: " << PORT << std::endl;

        std::cout << "Waiting for connection";
        ss = new Poco::Net::StreamSocket(serv->acceptConnection());
        ss->setNoDelay(true);
        auto ipaddr = ss->peerAddress().host().toString(); 
        auto port = ss->peerAddress().host().toString(); 
        std::cout << "\rConnected from " << ipaddr
        << ":" << port << std::endl;
        try {
            while (true) {
                auto str = tcp_read(*ss);
                std::cout << "rcv: " << str << std::endl;
                auto result = fizzbuzz(std::atoi(str.c_str()));
                tcp_send(*ss, result);
            } // while
        }
        catch (...) {
            ss->close();
            serv->close();
        }
    }

    return 0;
}

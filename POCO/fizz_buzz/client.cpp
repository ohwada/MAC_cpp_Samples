/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// Client-server Fizz-Buzz : Client
// reference: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_96c/main.cpp

#include <iostream>
#include "tcp_client.hpp"
#include "port.h"


/**
 * on_connect
 */
void on_connect(Poco::Net::StreamSocket *ss)
{

   const int MAX = 100;
   const long SLEEP = 1000; // 1 sec

    for(int i=1; i<MAX; i++) {
            auto request = std::to_string(i);
            tcp_send(*ss, request);
            std::cout << "send: " << request << std::endl;
            auto response = tcp_read(*ss);
            std::cout << "rcv: " << response << std::endl;
            Poco::Thread::sleep(SLEEP);
    }// for
}


/**
 * main
 */
int main() 
{
    std::string host = "localhost";

    run_client(host, PORT);

    return 0;
}


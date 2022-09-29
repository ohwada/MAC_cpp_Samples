/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Thread.h>
#include <boost/format.hpp>

#include "pico_tcp.hpp"
#include "port.h"


/**
 * main
 */
int main() 
{
    const long SLEEP = 1000; // 1 sec

   const int MAX = 100;

    std::string host = "localhost";

    while (true) {
        try {
            Poco::Net::StreamSocket *ss;
            auto address = Poco::Net::SocketAddress(host, PORT);
            ss = new Poco::Net::StreamSocket(address.family());
            ss->setNoDelay(true);
            ss->connect(address);
            std::cout << "Connect: " << address
        << ":" << PORT << std::endl;
            try {

                for(int i=0; i<MAX; i++) {
                    auto data = boost::str( boost::format("%03d") % i ) ;
                    tcp_send(*ss, data);
                    auto read = tcp_read(*ss);
                    std::cout << "rcv: " << read << std::endl;
                    Poco::Thread::sleep(SLEEP);
                }// for

            }
            catch (...) {
                ss->close();
            }
        }
        catch (...) {
            Poco::Thread::sleep(1000);
            std::cout << "Waiting for server to startup\n";
        }
    } // while

    return 0;
}


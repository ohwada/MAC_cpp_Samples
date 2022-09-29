/**
 * server.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>

#include <Poco/Net/Socket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>

#include "pico_tcp.hpp"
#include "port.h"


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
                std::string str = tcp_read(*ss);
                std::cout << "rcv: " << str << std::endl;
// echo back
                tcp_send(*ss, str);
       
            }
        }
        catch (...) {
            ss->close();
            serv->close();
        }
    }

    return 0;
}

/**
 * poco_tcp_server.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <Poco/Net/Socket.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>
#include "tcp.hpp"

// prototype
bool run_server(Poco::UInt16 port); 
void on_connect(   Poco::Net::StreamSocket *ss);


/**
 * run_server
 */
bool run_server(Poco::UInt16 port) 
{

        Poco::Net::ServerSocket *serv;
        Poco::Net::StreamSocket *ss;
        bool is_error = false;

    try{
        serv = new Poco::Net::ServerSocket(port);
        serv->listen();

        std::cout << "listen port: " << port << std::endl;

        std::cout << "Waiting for connection";
        ss = new Poco::Net::StreamSocket(serv->acceptConnection());
        ss->setNoDelay(true);
        auto ipaddr = ss->peerAddress().host().toString(); 
        auto port = ss->peerAddress().host().toString(); 
        std::cout << "\rConnected from " << ipaddr
        << ":" << port << std::endl;
        
            on_connect(ss);
    
        }
        catch (...) {
            is_error = true;
        }

        ss->close();
        serv->close();
    
    return !is_error;
}

/**
 * tcp_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Thread.h>
#include <boost/format.hpp>
#include "tcp.hpp"

// prototype
bool run_client( std::string host,  Poco::UInt16 port); 
void on_connect( Poco::Net::StreamSocket *ss);


/**
 * tcp_client
 */
bool run_client( std::string host,  Poco::UInt16 port) 
{

    bool is_error = false;

    Poco::Net::StreamSocket *ss;

    try {
            auto address = Poco::Net::SocketAddress(host, port);
            ss = new Poco::Net::StreamSocket(address.family());
            ss->setNoDelay(true);
            ss->connect(address);
            std::cout << "Connect: " << address << std::endl;
      
            on_connect(ss);
    
    }
    catch (std::runtime_error e) 
    {
        std::cerr << "runtime error: " << e.what() << std::endl;
       is_error = true;
    }
    catch(std::exception e)
    {
        std::cerr << e.what() << std::endl;
        is_error = true;
    }

   
        ss->close();

    return !is_error;
}

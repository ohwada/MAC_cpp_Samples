/**
 * poco_tcp_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Thread.h>
#include <boost/format.hpp>
#include "poco_tcp.hpp"

// prototype
bool tcp_client( std::string host,  Poco::UInt16 port, std::string send_data, std::string &recv_data); 


/**
 * tcp_client
 */
bool tcp_client( std::string host,  Poco::UInt16 port, std::string send_data, std::string &recv_data) 
{

    bool is_error = false;

    Poco::Net::StreamSocket *ss;

    try {
            auto address = Poco::Net::SocketAddress(host, port);
            ss = new Poco::Net::StreamSocket(address.family());
            ss->setNoDelay(true);
            ss->connect(address);
            std::cout << "Connect: " << address << std::endl;
       
            tcp_send(*ss, send_data);

            recv_data = tcp_read(*ss);
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

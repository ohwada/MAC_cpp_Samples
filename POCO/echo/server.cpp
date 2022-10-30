/**
 * server.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include "tcp_server.hpp"
#include "port.h"


/**
 * on_connect
 */
void on_connect(Poco::Net::StreamSocket *ss)
{
    while (true) {
            std::string str = tcp_read(*ss);
            std::cout << "rcv: " << str << std::endl;
// echo back
            tcp_send(*ss, str);
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

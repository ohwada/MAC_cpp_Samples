/**
 * client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include "tcp_client.hpp"
#include "port.h"

// global
int loop = 100;


/**
 *  on_connect
 */
void on_connect( Poco::Net::StreamSocket *ss)
{

    const long SLEEP = 1000; // 1 sec

    for(int i=0; i<loop; i++) {
        auto data = boost::str( boost::format("%03d") % i ) ;
        tcp_send(*ss, data);
        auto read = tcp_read(*ss);
        std::cout << "rcv: " << read << std::endl;
        Poco::Thread::sleep(SLEEP);
    }// for
}

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    if(argc == 2) {
      	loop = atoi( argv[1] );
    } else {
        cout << "Usage: " << argv[0] << " [loop] " << endl;
    }

    cout << "loop: " << loop << endl;

    std::string host = "localhost";

    run_client(host,  PORT); 

    return 0;
}


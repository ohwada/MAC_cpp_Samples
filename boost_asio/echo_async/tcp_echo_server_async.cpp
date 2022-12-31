/**
 *  tcp_echo_server_async.cpp
 * 2022-06-01 K.OHWADA
 */

// https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/async_tcp_echo_server.cpp


#include <iostream>
#include <cstdlib>
#include "echo_server_async.hpp"
#include "port.h"

using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    unsigned short port = PORT;

    if (argc == 2){
        port = std::atoi(argv[1]);
    } else {
      cerr << "Usage: async_tcp_echo_server <port> " << endl;
    }

    cout << "port: " << port << endl;

    run_server(port);

    return 0;
}

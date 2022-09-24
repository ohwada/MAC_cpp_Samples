/**
 * http_server.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Server with callback

#include <iostream>
#include "http_server.hpp"

using namespace std;


/**
 *  callback
 */
void callback( std::string msg)
{
    std::cout << "-----------------" << std::endl;
    std::cout << msg << std::endl;
    std::cout << "-----------------" << std::endl;

}


/**
 *  main
 */
int main(int argc, char *argv[])
{

    int port = 8080;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        cerr << "Usage: " << argv[0] << " [port] " << endl;
    }

    cout << "port: " << port << endl;

   run_server(port, callback);

    return 0;
}

// listen port: 8080

/**
 * http_client.cpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Client
// reference : https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

// g++ http_client.cpp -std=c++11 `pkg-config --cflags --libs boost` -o bin/client


#include <iostream>
#include <boost/asio.hpp>
#include "asio_socket.hpp"
#include "resolver.hpp"
#include "http_client.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{


    int port = PORT_HTTP;

    string path = ROOT_PATH;

    if(argc == 3) {
      port = atoi( argv[1] );
      path = argv[2];
    } else if(argc == 2) {
      port = atoi( argv[1] );
    } else {
        cout << "Usage: " << argv[0] << " [port] " << endl;
    }

      cout << "port: " << port << endl;
      cout << "path: " << path << endl;

    string host("localhost");

    string request =
     build_http_request( host, path);

    cout << endl;
    cout << "request" << endl;
    cout << request << endl;

    string response;
    bool ret = localhost_client(port, request, response);
if( !ret ){
    cerr << "localhost client faild" << endl;
}

    cout << endl;
    cout << "response" << endl;
    cout << response << endl;

    return EXIT_SUCCESS;
}

/**
 *  http_async_client.cpp
 * 2022-06-01 K.OHWADA
 */

// https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/async_client.cpp

#include <iostream>
#include <string>
#include "http_client_async.hpp"


 using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{
    string server("example.com");
    string port("80");
    string path("/");

    if (argc == 4) {
        server =  argv[1];
        port =  argv[2];
        path =  argv[3];
    } else if (argc == 3) {
        server =  argv[1];
        port =  argv[2];
    } else {
      cout << "Usage: async_client <server> <port> <path>\n";
      cout << "Example:\n";
      cout << "  async_client www.boost.org 80 /LICENSE_1_0.txt\n";
    }

    cout << "server: " << server << endl;
    cout << "port: " << port << endl;
    cout << "path: " << path << endl;

    http_client_async(server, port, path);

  return 0;
}


// request
// GET / HTTP/1.1
// Host: example.com
// response
// http_version: HTTP/1.1
// status_code: 200
// status_message:  OK
// <title>Example Domain</title>


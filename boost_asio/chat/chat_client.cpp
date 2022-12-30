/**
 * chat_client.cpp
 * 2022-06-01 K.OHWADA
 */


// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/chat_client.cpp


#include <iostream>
#include "chat_client.hpp"
#include "port.h"


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string host("localhost");
    string port = std::to_string( PORT );

    if (argc == 3)
    {
        host = argv[1];
        port = argv[2];
    } else {
      cout << "Usage: chat_client <host> <port> " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    chat_client(host, port);

  return 0;
}

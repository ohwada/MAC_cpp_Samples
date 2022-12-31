/**
 * tcp_echo_client_async.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/blocking_tcp_echo_client.cpp

#include <iostream>
#include "echo_client_async.hpp"
#include "echo_client.hpp"
#include "port.h"

// global
int data_cnt = 0;


/**
 * get_write_data
 */
 std::string get_write_data()
{
// 1 sec
    const int SLEEP = 1000;

    const int DATA_LIMIT = 10;

    data_cnt ++;
    if(data_cnt > DATA_LIMIT ){
        return "";
    }

    auto data = build_write_data(data_cnt );
    thread_sleep(SLEEP);
    return data;
}


    using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string host("localhost");
    
    string port = to_string(PORT);


    if(argc == 3) {
      	host = argv[1];
      	port = argv[2];
    } else {
        cout << "Usage: " << argv[0] << " [host] [port] " << endl;
    }

    cout << "host: " << host << endl;
    cout << "port: " << port << endl;

    echo_client(host, port);

  return 0;
}

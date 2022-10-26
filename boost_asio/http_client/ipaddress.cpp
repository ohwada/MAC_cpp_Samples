/**
 * ipaddress.cpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include "resolver.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    std::string host("example.com");

    if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [host] " << endl;
    }

    cout << "host: " << host << endl;

    boost::asio::ip::address address;
    std::string error;

    bool ret1 = get_address( host, address, error );
    if(!ret1){
        cerr << "get_address: " << error << endl;
        return EXIT_FAILURE;
    }

// TODO:
// IPV4 format
    cout <<  address.to_string() << endl;

    return EXIT_SUCCESS;
}


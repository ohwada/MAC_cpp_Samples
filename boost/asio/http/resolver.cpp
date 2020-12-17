/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// resolve IP Address from hostname

//  reference :https://stackoverflow.com/questions/31314433/how-do-i-convert-a-host-name-in-to-a-boost-address-or-endpoint

// g++ resolvercpp -std=c++11 `pkg-config --cflags --libs boost`

#include <iostream>
#include <string>
#include "resolver.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string host("example.com");

    if(argc == 2) {
      	host = argv[1];
    } else {
        cout << "Usage: " << argv[0] <<  " [host] " << endl;
    }

    cout << "host: " << host << endl;

    string ipaddr;
    string error;

    bool ret = get_ipaddress(host, ipaddr, error);

    if(ret){
        cout << "ip address: " << ipaddr << endl;
    } else {
        cerr << "error: " << error << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
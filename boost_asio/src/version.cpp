/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// display version

#include <iostream>
#include <string>
#include <boost/asio/version.hpp>

using namespace std;

    
/**
 * main
 */
int main(void)
{
    const string DOT(".");

    int major = BOOST_ASIO_VERSION / 100000;
    int minor =  ( BOOST_ASIO_VERSION / 100 ) % 1000;
    int sub_minor = BOOST_ASIO_VERSION % 100;

    cout << "boost/asio version: "  << major << DOT << minor << DOT << sub_minor << endl;

    return EXIT_SUCCESS;
}


// boost/asio version: 1.22.2


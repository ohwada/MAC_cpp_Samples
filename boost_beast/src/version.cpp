/**
 * version
 * 2022-06-01 K.OHWADA
 */

// display version

#include <iostream>
#include <string>
#include <boost/beast/version.hpp>

using namespace std;

    
/**
 * main
 */
int main(void)
{
    const string DOT(".");

    int major = BOOST_BEAST_VERSION / 100000;
    int minor =  ( BOOST_BEAST_VERSION / 100 ) % 1000;
    int sub_minor = BOOST_BEAST_VERSION % 100;

    cout << "boost/beast version: "  << major << DOT << minor << DOT << sub_minor << endl;

    return 0;
}

// boost/beast version: 0.3.30


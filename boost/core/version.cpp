/**
 * version.cpp
 * 2020-07-01 K.OHWADA
 */

// display version

#include <iostream>
#include <boost/version.hpp>

using namespace std;

    
/**
 * main
 */
int main(void)
{

    cout << "boost version: " << BOOST_LIB_VERSION << endl;

    return EXIT_SUCCESS;
}


// boost version: 1_73


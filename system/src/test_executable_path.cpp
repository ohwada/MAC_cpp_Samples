/**
 * system sample
 * 2020-07-01 K.OHWADA
 */

 // get executable path for macOS
// test for executable_path.hpp

#include <iostream>
#include "executable_path.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    string cmd( argv[0] );

    cout << "cnd: " << cmd << endl;

    string dir = 
    getExecutablePathDir( cmd );

    cout << "executable path: " << dir << endl;

    return EXIT_SUCCESS;
}


// cnd: ./a.out
// executable path: /Users/taro/hoge/

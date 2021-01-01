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

    cout << "argv0: " << argv[0] << endl;

    string dir = 
    getExecutablePathDir( argv[0] );

    cout << "executable path: " << dir << endl;

    return EXIT_SUCCESS;
}

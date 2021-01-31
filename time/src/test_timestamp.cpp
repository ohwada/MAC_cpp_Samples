/**
 * time sample
 * 2020-10-01 K.OHWADA
 */

// display timesatamp file name

// g++ test_timestamp.cpp  -std=c++11

#include <iostream>
#include "timestamp.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const string prefix("file");
    const string ext("txt");

    string filename;

    getTimestampFileName( prefix, ext,  filename );

    cout << filename << endl;

    return EXIT_SUCCESS;
}


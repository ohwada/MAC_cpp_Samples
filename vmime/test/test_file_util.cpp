/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for file_util.hpp and getTimestampFileName

// g++ test_file_util.cpp -std=c++11

#include <iostream>
#include <string>
#include "../pop3/file_util.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    string prefix = "hoge";
    string ext = "txt";
    string file;
    getTimestampFileName( prefix, ext, file );

    system( "date" );

    cout << "file: " << file << endl;

    return EXIT_SUCCESS;
}


// hoge_2020103115922.txt

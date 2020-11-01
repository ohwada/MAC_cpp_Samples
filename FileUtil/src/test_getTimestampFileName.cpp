/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */


// test for getTimestampFileName

// g++  src/test_getTimestampFileName.cpp -std=c++11

#include <iostream>
#include <string> 
#include "file_util.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const std::string prefix("hoge");
    const std::string ext("txt");
    std::string filename;

    getTimestampFileName(prefix, ext, filename);

    cout << filename << endl;

    return EXIT_SUCCESS;
}


// hoge_20201031140214.txt




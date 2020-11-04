/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for getTimestampFileName

#include <iostream>
#include <string>
#include "file_time.hpp"

#include <cstdlib>

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

    return 0;
}


// hoge_2020_10_3_11_59_22.txt

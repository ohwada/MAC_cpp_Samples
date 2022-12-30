/**
 *  test_image_file.cpp
 * 2022-06-01 K.OHWADA
 */ 


#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
#include "base64.h"
#include "file_util.hpp"

using namespace std;


/**
 *  main
 */
int main(void) 
{
    const size_t BUFSIZE = 128;
   char cmd[BUFSIZE];

    string file_in("images/sample.png");
    string file_out("out/sample.png");

    std::vector<char> data;

    bool ret1 = readBinaryFile1(file_in, data);
    if( !ret1 ){
        cerr << "readBinaryFile1 failed" << endl;
    }

    cout << "data size: " << data.size() << endl;


    auto b64 = base64_encode( (unsigned char *)data.data(), data.size() );
     
    cout << "b64 size: " << b64.size() << endl;

    auto data2 = base64_decode(b64);
  
    cout << "data2 size: " << data2.size() << endl;

    bool ret2 = writeBinaryFile2(file_out, data2);
    if(!ret2){
        cerr << "writeBinaryFile2 failed" << endl;
    }


    char FORMAT[] = "cmp %s %s";

    snprintf(cmd, BUFSIZE, (char *)FORMAT, (char *)file_in.c_str(), (char *)file_out.c_str() );

    cout << "cmd: " << cmd << endl;

    int res = system( cmd );

    cout << "res: " << WEXITSTATUS(res) << endl;

    assert( WEXITSTATUS(res) == 0);

    cout << "successful" << endl;

    return 0;
}

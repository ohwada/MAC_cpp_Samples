/**
 *  test_image_file.cpp
 * 2022-06-01 K.OHWADA
 */ 


#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
#include <boost/format.hpp>
#include "base64.hpp"
#include "file_util.hpp"

using namespace std;


/**
 *  main
 */
int main(void) 
{

    string file_in("images/sample.png");
    string file_out("out/sample.png");

    std::vector<char> data;

    bool ret1 = readBinaryFile1(file_in, data);
    if( !ret1 ){
        cerr << "readBinaryFile1 failed" << endl;
    }

    cout << "data size: " << data.size() << endl;

    auto b64 = encode_base64(data);
    
    cout << "b64 size: " << b64.size() << endl;

    auto bin = decode_base64(b64);
  
    cout << "bin size: " << bin.size() << endl;

    bool ret2 = writeBinaryFile1(file_out, bin);
    if(!ret2){
        cerr << "writeBinaryFile1 failed" << endl;
    }

    string FORMAT("cmp %s %s");

    auto cmd = 
    boost::str( boost::format(FORMAT) % file_in %file_out );

    cout << "cmd: " << cmd << endl;

    int res = system( cmd.c_str() );

    cout << "res: " << WEXITSTATUS(res) << endl;

    assert( WEXITSTATUS(res) == 0);

    cout << "successful" << endl;

    return 0;
}

 /**
   * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for readAttchmentJsonFile
// g++ src/test_readAttchmentJsonFile.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include <string>
#include "attchment_decode.hpp"



using namespace std;

/**
 *  main
 */
int main(int argc, char* argv[])
{

    string file_json("sample_attach.json");

    string file_binary("sample.png");


    if(argc == 3){
        file_json = argv[1];
        file_binary = argv[2];
    } else if(argc == 2){
        file_json = argv[1];
    } else {
        cout << "usage: " <<  argv[0] << "[amejson file] [binary file] " << endl;
    }

    string error;
    bool ret = parse_decode_AttchmentJsonFile_to_file( file_json, file_binary, error);

    if(ret){
        cout << "saved: " << file_binary << endl;
    } else {
        cout << "parse_decode_AttchmentJsonFile_to_file: " << error << endl;
    }

  return EXIT_SUCCESS;
}



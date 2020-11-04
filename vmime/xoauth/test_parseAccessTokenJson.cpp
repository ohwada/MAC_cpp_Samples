 /**
 * mail sample
 * 2020-07-01 K.OHWADA
 */

// test for parseAccessTokenJson
// g++ xoauth/test_parseAccessTokenJson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "auth_json.hpp"
#include "file_util.hpp"

using namespace std;



/**
 *  main
 */
int main(int argc, char* argv[])
{

    string access_file = "access_token.json";

    if(argc == 2){
        access_file = argv[1];
    } else {
        cout << "usage: " <<  argv[0] << " [file] " << endl;
    }


// access token
    cout << "access file: " <<  access_file << endl;


    string access_data;
    bool ret1 = readTextFile( access_file, access_data );
    if(!ret1){
        cout << "eadTextFile failed: " <<  access_file  << endl;
    }


    string access_token;
    string error;
    bool ret2 = parseAccessTokenJson( access_data, access_token, error );
    if(ret2){
        cout << "access_token: " << access_token << endl;
    } else {
        cout << "parseAccessTokenJson error: " <<  error << endl;
    }

  return 0;
}


// access file: assets/sample_access_token.json
// access_token: dummy access token


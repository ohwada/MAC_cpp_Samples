 /**
   * test_readRefreshTokenJsonFile.cpp
 * 2022-06-01 K.OHWADA
 */

// test for readRefreshTokenJsonFile
// g++ test/test_src_readRefreshTokenJsonFile.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include <cassert>
#include "../oauth2/oauth_read_refresh_token.hpp"


using namespace std;



/**
 *  main
 */
int main(int argc, char* argv[])
{

    string refresh_file = "samples/sample_refresh_token.json";

    if(argc == 2){
        refresh_file = argv[1];
    } else {
        cout << "usage: " <<  argv[0] << "[file] " << endl;
    }

// refresh file
    cout << endl;
    cout << "refresh file: " <<   refresh_file << endl;

    string refresh_token;
    string error;
    bool ret = readRefreshToken( refresh_file, refresh_token, error);
    if(ret){
        cout << "refresh_token: " << refresh_token << endl;
    } else {
        cout << " readRefreshToken error: " << error << endl;
    }

    assert(refresh_token == "dummy refresh token");

    cout << "successful" << endl;

  return EXIT_SUCCESS;
}


//refresh file: data/sample_refresh_token.json
// refresh_token: dummy refresh token



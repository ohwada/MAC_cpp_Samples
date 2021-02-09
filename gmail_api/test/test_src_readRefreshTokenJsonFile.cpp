 /**
   * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for readRefreshTokenJsonFile
// g++ test/test_src_readRefreshTokenJsonFile.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "../src/json_auth.hpp"


using namespace std;



/**
 *  main
 */
int main(int argc, char* argv[])
{

    string refresh_file = "refresh_token_readonly.json";

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
    bool ret = readRefreshTokenJsonFile( refresh_file, refresh_token, error);
    if(ret){
        cout << "refresh_token: " << refresh_token << endl;
    } else {
        cout << " readRefreshTokenJsonFile error: " << error << endl;
    }

  return EXIT_SUCCESS;
}


//refresh file: data/sample_refresh_token.json
// refresh_token: dummy refresh token



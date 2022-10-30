 /**
  * test_parseAccessTokenJson.cpp
 * 2022-06-01 K.OHWADA
 */

// test for  parseAccessTokenJson
// g++ test/test_src_parseAccessTokenJson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`


#include <iostream>
#include <string>
#include <cassert>
#include "../oauth2/json_oauth.hpp"
#include "file_util.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    string file( "samples/sample_access_token.json" );

    if(argc == 2){
        file = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [accessTokenJsonFile]" << endl;
    }

// access token
    cout << "access token file: " << file << endl;

    string text;
    bool ret1 = readTextFile(file, text);
    if(!ret1){
        cout << "readTextFile error:" << file << endl;
	    return EXIT_FAILURE;
    }

    string access_token;
std::string scope;
std::string token_type;
    string error;

    bool ret2 = parseAccessTokenJson( 
text, access_token, scope, token_type, error);
    if(ret2 ){
        cout << "access_token: " << access_token << endl;
       cout << " scope: " <<  scope << endl;
       cout << "token_type: " << token_type << endl;
    } else {
        cout << error << endl;
    }

    assert(access_token == "dummy access token");

    cout << "successful" << endl;

	return EXIT_SUCCESS;
}


// access token file: data/sample_access_token.json
// access_token: dummy access token


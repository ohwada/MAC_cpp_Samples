 /**
  * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for  parseAccessTokenJson
// g++ src/test_parseAccessTokenJson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`


#include <iostream>
#include <string>
#include "auth_json.hpp"


/**
 *  readTextFile
 */
bool readTextFile( std::string file, std::string &text )
{
    const std::string LF = "\n";

    std::ifstream fin;

    // open input file
    fin.open(file, std::ios::in); 
    if (fin.fail()){ 
        return false;
    }                         

    // read text  by one line
    std::string line;
    while( getline(fin, line) ) {
        text += line + LF;
    }

    return true;
}

using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    string file( "access_token.json" );

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
    string error;

    bool ret2 = parseAccessTokenJson( text, access_token, error );
    if(ret2 ){
        cout << "access_token: " << access_token << endl;
    } else {
        cout << error << endl;
    }

	return EXIT_SUCCESS;
}


// access token file: data/sample_access_token.json
// access_token: dummy access token


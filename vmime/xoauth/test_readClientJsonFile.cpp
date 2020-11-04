 /**
 * mail sample
 * 2020-07-01 K.OHWADA
 */

// test for readClientJsonFile
// g++ xoauth/test_readClientJsonFile.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "auth_json.hpp"
#include "mail_directory.h"

using namespace std;



/**
 *  main
 */
int main(int argc, char* argv[])
{

    string client_file = getMailDir() + std::string("/client_credentials.json");

    if(argc == 2){
        client_file =  argv[1];
    } else {
        cout << "usage: " <<  argv[0] << " [file] " << endl;
    }

// client file
    cout << "client file: " <<  client_file << endl;

    string client_id;
    string client_secret;
    string error;
    bool ret = readClientJsonFile(client_file, client_id, client_secret, error);
    if(ret){
        cout << "client_id: " << client_id << endl;
        cout << "client_secret: " << client_secret << endl;
    } else {
        cout << " readClientJsonFile error: " << error << endl;
    }

  return 0;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


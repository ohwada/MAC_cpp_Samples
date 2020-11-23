 /**
  * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for readClientJsonFile
// gcc test_readClientJsonFile.cpp `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "auth_json.hpp"
#include "mail_json.hpp"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    string file + getMailDir() + string("/client_credentials.json");

    if(argc == 2){
        file = argv[1];
    } else {
        cout << "usage: " << argv[0] << " [clientJsonFile]" << endl;
    }

// client file
    cout << "client file: " << file << endl;

    string client_id;
    string client_secret;
    string error;
    bool ret = readClientJsonFile(file, client_id, client_secret, error);
    if(ret){
        cout << "client_id: " << client_id ;
        cout << "client_secret: " << client_secret << endl;
    } else {
        cout << error << endl;
    }

    return EXIT_SUCCESS;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


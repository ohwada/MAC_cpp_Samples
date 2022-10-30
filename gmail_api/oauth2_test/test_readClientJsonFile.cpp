 /**
  * test_readClientJsonFile.cpp
 * 2022-06-01 K.OHWADA
 */

// test for readClientJsonFile

// g++ test/test_src_readClientJsonFile.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include <cassert>
#include "../oauth2/json_oauth.hpp"
#include "../oauth2/mail_directory.h"


using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    //string file = getMailDir() + string("/client_credentials.json");

    string file("samples/sample_client_credentials.json");

    string client_id;
    string client_secret;
    string error;
    bool ret = readClientJsonFile(file, client_id, client_secret, error);
    if(ret){
        cout << "client_id: " << client_id << endl;
        cout << "client_secret: " << client_secret << endl;
    } else {
        cout << error << endl;
    }

    assert(client_id == "dummy client id");
    assert(client_secret == "dummy client secret");

   cout << "successful" << endl;

    return EXIT_SUCCESS;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


/**
 * request_sccess_token.cpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include "oauth_request_sender.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    std::string access_token;
    std::string error;
    bool is_verbose = true;

    bool ret = getNewAccessToken(access_token, error, is_verbose );
    if( !ret){
        cerr << "getNewAccessToken: " << error << endl;
        return EXIT_FAILURE;
    }

    printAccessToken(access_token);

    return EXIT_SUCCESS;
}


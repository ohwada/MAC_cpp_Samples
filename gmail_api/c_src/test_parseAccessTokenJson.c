 /**
  * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for  parseAccessTokenJson
// gcc test_parseAccessTokenJson.c `pkg-config --cflags --libs json-c`


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "auth_json.h"
#include "file_util.h"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    char* file = "access_token.json";

    if(argc == 2){
        file = argv[1];
    } else {
        printf( "usage: %s [accessTokenJsonFile]" ,  argv[0] );
    }

// access token
    printf("access token file: %s \n", file );

    char error[100];
    char* data = readTextFile(file, error);
    if(!data){
        printf("error: %s, \n", error);
        return EXIT_FAILURE;
    }

    char access_token[100];
    bool ret = parseAccessTokenJson( data, access_token, error );
    if( ret ){
        printf("access_token: %s, \n", access_token);
    } else {
        printf("error: %s, \n", error);
    }

       return EXIT_SUCCESS;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


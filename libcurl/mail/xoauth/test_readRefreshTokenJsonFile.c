 /**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// test for   readRefreshTokenJsonFile
// gcc test_readRefreshTokenJsonFile.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include "auth_json.h"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    const size_t BUFSIZE = 100;
    char file[BUFSIZE];

    strcpy( file, "refresh_token.json" );

    if(argc == 2){
        strcpy(file, argv[1]);
    } else {
        printf( "usage: %s [refreshTokenJsonFile]" ,  argv[0] );
    }


// refresh file
    printf("refresh token file: %s \n", file );

    char refresh_token[100];
    char error[100];
    int ret = readRefreshTokenJsonFile( file, refresh_token, error);
    if(ret == 0){
        printf( "refresh_token: %s \n", refresh_token );
    } else {
        printf("error: %s \n", error);
    }

    return 0;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


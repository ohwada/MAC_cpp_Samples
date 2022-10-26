 /**
 * test_readRefreshTokenJsonFile.c
 * 2022-06-01 K.OHWADA
 */

// test for   readRefreshTokenJsonFile
// gcc test_readRefreshTokenJsonFile.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "file_util.h"
#include "../xoauth/auth_json.h"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    const size_t BUFSIZE = 128;
    char path[BUFSIZE];
  char refresh_token[BUFSIZE];
    char error[BUFSIZE];

    char* dir = "sample";
    char* file = "sample_refresh_token.json";

    make_path(dir, file, (char *)path );

    bool ret = readRefreshTokenJsonFile( (char *)path, (char *)refresh_token, (char *)error);
    if(!ret){
        printf("error: %s \n", error);
       return EXIT_FAILURE;
    }

    printf( "refresh_token: %s \n", refresh_token );

    assert( strcmp(refresh_token, "1//dummy.token") == 0);

    printf("successful \n");

    return EXIT_SUCCESS;
}




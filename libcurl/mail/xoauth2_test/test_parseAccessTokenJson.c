 /**
 * test_parseAccessTokenJson.c
 * 2022-06-01 K.OHWADA
 */

// test for  parseAccessTokenJson
// gcc test_parseAccessTokenJson.c `pkg-config --cflags --libs json-c`


#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "file_util.h"
#include "../xoauth2/auth_json.h"



/**
 *  main
 */
int main(int argc, char* argv[])
{

    const size_t BUFSIZE = 1024;
    char path[BUFSIZE];
   char text[BUFSIZE];
    char access_token[BUFSIZE];
    char error[BUFSIZE];

    char* dir = "sample";
    char* file = "sample_access_token.json";

    make_path(dir, file, (char *)path );

    bool ret1 = file_text_read2( (char *)path, (char *)text, (char *)error);
    if(!ret1){
        printf("error: %s, \n", error);
        return EXIT_FAILURE;
    }

    bool ret2 = parseAccessTokenJson( (char *)text, (char *)access_token, (char *)error );
    if( !ret2 ){
        printf("error: %s, \n", error);
        return EXIT_FAILURE;
    }

  printf("access_token: %s \n", access_token);

  assert( strcmp(access_token, "ya29.a0dummy-token") == 0);

    printf("successful \n");

       return EXIT_SUCCESS;
}


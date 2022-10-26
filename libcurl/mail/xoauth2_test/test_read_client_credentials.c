 /**
 * test_readClientJsonFile.c
 * 2020-07-01 K.OHWADA
 */

// test for readClientJsonFile
// gcc test_readClientJsonFile.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../xoauth2/client_credentials.h"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    const size_t BUFSIZE = 128;
    char path[BUFSIZE];
    char client_id[BUFSIZE];
    char client_secret[BUFSIZE];
    char error[BUFSIZE];

    bool ret1 = read_client_credentials( (char *)client_id, (char *)client_secret, (char *)error );
    if(!ret1){
        fprintf(stderr, "error: %s \n", error);
       return EXIT_FAILURE;
    }

    printf( "client_id: %s \n", client_id );
    printf( "client_secret: %s \n",client_secret);



    char* dir = "sample";
    char* file = "sample_client_credentials.json";

    make_path(dir, file, (char *)path );

  bool ret2 = readClientJsonFile( (char *)path, (char *)client_id, (char *)client_secret, (char *)error);
    if(!ret2){
        fprintf(stderr, "error: %s \n", error);
       return EXIT_FAILURE;
    }

    printf( "client_id: %s \n", client_id );
    printf( "client_secret: %s \n",client_secret);

    assert( strcmp(client_id, "dummy-id.com") == 0);

    assert( strcmp(client_secret, "dummy-secret") == 0);

    printf("successful \n");

    return EXIT_SUCCESS;
}


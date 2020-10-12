 /**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// test for readClientJsonFile
// gcc test_readClientJsonFile.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include "auth_json.h"
#include "mail_json.h"


/**
 *  main
 */
int main(int argc, char* argv[])
{

    const size_t BUFSIZE = 100;
    char file[BUFSIZE];

    strcpy( file, getMailDir() );
    strcat( file, "/client_credentials.json");

    if(argc == 2){
        strcpy(file, argv[1]);
    } else {
        printf( "usage: %s [clientJsonFile]" ,  argv[0] );
    }

// client file
    printf("client file: %s \n", file );

    char client_id[100];
    char client_secret[100];
    char error[100];
    int ret = readClientJsonFile(file, client_id, client_secret, error);
    if(ret == 0){
        printf( "client_id: %s \n", client_id );
        printf( "client_secret: %s \n",client_secret);
    } else {
        printf("error: %s \n", error);
    }

  return 0;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


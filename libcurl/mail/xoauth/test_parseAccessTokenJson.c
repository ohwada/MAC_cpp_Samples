 /**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// test for  parseAccessTokenJson
// gcc test_parseAccessTokenJson.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "auth_json.h"


/**
 * readTextFile
 */
char* readTextFile(char *file, char *error)
{

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    // Seek the last byte of the file
    fseek(fp, 0, SEEK_END);
     
    // Offset from the first to the last byte, or in other words, filesize
    int string_size = ftell(fp);

    // go back to the start of the file
    rewind(fp);

    // Allocate a string that can hold it all
    char* buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

    // Read it all in one operation
    int read_size = fread(buffer, sizeof(char), string_size, fp);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[string_size] = '\0';

    if (string_size != read_size){
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    // Always remember to close the file.
    fclose(fp);

    return buffer;
}


/**
 *  main
 */
int main(int argc, char* argv[])
{

 const size_t BUFSIZE = 100;
    char file[BUFSIZE];

    strcpy( file, "access_token.json" );

    if(argc == 2){
        strcpy(file, argv[1]);
    } else {
        printf( "usage: %s [accessTokenJsonFile]" ,  argv[0] );
    }

// access token
    printf("access token file: %s \n", file );

    char error[100];
    char* data = readTextFile(file, error);
    if(!data){
        printf("error: %s, \n", error);
        return 1;
    }

    char access_token[100];
    int ret = parseAccessTokenJson( data, access_token, error );
    if(ret == 0){
        printf("access_token: %s, \n", access_token);
    } else {
        printf("error: %s, \n", error);
    }

  return 0;
}


// client file: assets/sample_client_secret.json
// client_id: dummy client id
// client_secret: dummy client secret


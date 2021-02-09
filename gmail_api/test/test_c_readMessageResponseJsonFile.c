/**
  * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for readMessageResponseJsonFile

// gcc test/test_c_readMessageResponseJsonFile.c `pkg-config --cflags --libs json-c`


#include <stdio.h>
#include <stdlib.h>
#include "../c_src/json_response.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    const char*  file = "samples/sample_msg_response.json";

   if(argc == 2){
        file = argv[1];
    } else {
        printf( "usage: %s [responseJsonFile] \n" ,  argv[0] );
    }

// client file
    printf("response file: %s \n", file );


    char id[100];
    char subject[100];
    char from[100];
    char date[100];
    char snippet[500];

    char error[100]; 
    bool is_verbose = true;

    bool ret = readMessageResponseJsonFile( 
    (char *)file, 
    id, subject, from, date, snippet,
    error, is_verbose) ;

    if( !ret ){
        printf("error: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("\n");
    printf("id: %s \n", id);
    printf("subject: %s \n", subject);
    printf("from: %s \n", from);
    printf("date: %s \n", date);
    printf("snippet: %s \n", snippet);


    return EXIT_SUCCESS;
}


// id: sample id 
// subject: sample subject 
// from: taro@example.com 
// date: Mon, 12 Oct 2020 12:16:38 GMT 
// snippet: this is sample snippet 


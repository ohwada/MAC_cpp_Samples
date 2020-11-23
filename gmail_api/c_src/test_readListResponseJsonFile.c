/**
  * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// test for readListResponseJsonFile

// gcc c_src/test_readListResponseJsonFile.c `pkg-config --cflags --libs json-c`

#include <stdio.h>
#include <stdlib.h>
#include "response_json.h"
#include "char_array.h"


/**
 * main
 */
int main(int argc, char* argv[])
{

    const char*  file = "data/sample_list_response.json";

   if(argc == 2){
        file = argv[1];
    } else {
        printf( "usage: %s [responseJsonFile]" ,  argv[0] );
    }

// response file
    printf("response file: %s \n", file );

    const int IDS_SIZE = 10;
    const int ID_LENGTH = 100;

    char** ids = alloc_chars(IDS_SIZE, ID_LENGTH) ;

    if(!ids){
        printf("can not allocate memory \n");
        return EXIT_FAILURE;
    }

    int list_num;
    char error[100]; 
    bool is_verbose = true;

// get id list
    bool ret = readListResponseJsonFile( (char *)file, ids, IDS_SIZE, &list_num, error, is_verbose); 

    int exit;

    if(ret){
        printf("\n");
        printf("list num: %d mails \n", list_num);
        print_chars(ids, IDS_SIZE);
        exit = EXIT_SUCCESS;
    } else {
        printf("error: %s \n", error);
        exit = EXIT_FAILURE;
    }

    free_chars(ids, IDS_SIZE);

    return exit;
}

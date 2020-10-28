/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// get HTTP page
// copy into memory

#include <stdio.h>
#include <stdlib.h>
#include "url_write.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    char* url = "http://example.com";

    if(argc == 2) {
        url = argv[1];
    } else {
        printf("Usage: %s [url] \n", argv[0]);
    }

    printf("url: %s \n", url);

    struct CurlMemory mem;
    char error[100];
  bool is_verbose = true;

    bool ret = url_to_memory(url, &mem, error, is_verbose );

    int exit;
    if(ret){
        printCurlMemory(mem);
        exit = EXIT_SUCCESS;
    } else {
        printf("url_to_memory: %s \n", error);
        exit =  EXIT_FAILURE;
    }

    return exit;
}


// Connected to example.com
// <title>Example Domain</title>



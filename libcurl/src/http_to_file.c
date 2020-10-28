/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// get HTTP page
// save into a local file

#include <stdio.h>
#include <stdlib.h>
#include "url_write.h"


/**
 * main
 */

int main(int argc, char* argv[])
{

   char  *url = "http://example.com";
    char *file = "example_com.html";


    if(argc == 3) {
        url = argv[1];
        file = argv[2];
    } else {
        printf("Usage: %s [url] [file] \n", argv[0]);
    }

    printf("url: %s \n", url);

    printf("file: %s \n", file);

    char error[100];
    bool is_verbose = true;

    bool ret = url_to_file(url,  file, error, is_verbose);

    int exit;
    if(ret){
        printf("saved to: %s \n", file);
        exit = EXIT_SUCCESS;
} else {
        printf("url_to_file: %s \n", error);
        exit = EXIT_FAILURE;
    }

    return exit;
}

// Connected to example.com 
// saved to: example_com.html 


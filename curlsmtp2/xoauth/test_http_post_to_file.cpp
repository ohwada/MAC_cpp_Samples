/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// post to postman echo server,  save response to local file
// test for http_post_to_file

 // g++ xoauth/test_http_post_to_file.cpp  -std=c++11 `pkg-config --cflags --libs libcurl`  

#include <stdio.h>
#include <stdlib.h>
#include "curl_http_post_write.h"


/**
 * main
 */
int main(void)
{
    const char URL[] = "https://postman-echo.com/post";

    const char OUTPUT[] = "http_post_to_file_result.txt";

    const char POSTFILEDS[] ="project=curl_file&name=michael&age=30";

    char error[100];
    bool is_verbose = true;

    bool ret = http_post_to_file( (char *)URL, (char *)POSTFILEDS, (char *)OUTPUT, error, is_verbose);
    if(ret){
        printf("saved to: %s \n", OUTPUT);
    } else {
        printf("http_post_to_file: %s \n", error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// Connected to postman-echo.com
// saved to: http_post_to_file_result.txt 



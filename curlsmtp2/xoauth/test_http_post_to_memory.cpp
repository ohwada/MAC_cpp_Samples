/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// post to postman echo server,  copy response to memory <br/>
// test for http_post_to_memory

 // g++ xoauth/test_http_post_to_memory.cpp  -std=c++11 `pkg-config --cflags --libs libcurl`  

#include <stdio.h>
#include <stdlib.h>
#include "curl_http_post_write.h"


/**
 * main
 */
int main(void)
{
    const char URL[] = "https://postman-echo.com/post";

    const char POSTFILEDS[] = "project=curl_mem&name=daniel&age=20";

    struct CurlMemory mem;

    char error[100];
    bool is_verbose = true;


    bool ret = http_post_to_memory( (char *)URL, (char *)POSTFILEDS, &mem, error, is_verbose);
    if(ret){
        printCurlMemory(mem);
    } else {
        printf("http_post_to_memory: %s \n", error);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// Connected to postman-echo.com
// {"project":"curl_mem","name":"daniel","age":"20"}



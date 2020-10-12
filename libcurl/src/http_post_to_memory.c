/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// post to postman echo server,  copy response to memory <br/>
// test for http_post_to_memory

#include <stdio.h>
#include "http_post.h"


/**
 * main
 */
int main(void)
{
    const char URL[] = "https://postman-echo.com/post";

    const char POSTFILEDS[] = "project=curl_mem&name=daniel&age=20";

    struct CurlMemory mem;

    int verbose = 1;

// to memory


    int ret = http_post_to_memory( (char *)URL, (char *)POSTFILEDS, &mem, verbose);
    if(ret == 0){
        printCurlMemory(mem);
    } else {
        printf("http_post_to_memory faild");
    }

    return 0;
}


// {"project":"curl_mem","name":"daniel","age":"20"}
// saved to: http_post_result.txt 


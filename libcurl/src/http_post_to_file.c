/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// post to postman echo server,  save response to local file
// test for http_post_to_file

#include <stdio.h>
#include "http_post.h"


/**
 * main
 */
int main(void)
{
    const char URL[] = "https://postman-echo.com/post";

    const char OUTPUT[] = "http_post_to_file_result.txt";

    const char POSTFILEDS[] = "project=curl_file&name=michael&age=30";

    int verbose = 1;

    int ret = http_post_to_file( (char *)URL, (char *)POSTFILEDS, (char *)OUTPUT, verbose);
    if(ret == 0){
        printf("saved to: %s \n", OUTPUT);
    } else {
        printf("http_post_to_file faild \n");
    }

    return 0;
}

// Connected to postman-echo.com (3.233.236.182) port 443 (#0)
// saved to: http_post_to_file_result.txt 


/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// display curl version


#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>


/**
 * main
 */
int main(void)
{
    printf("curl version: %s \n", curl_version() );

    return EXIT_SUCCESS;
}


// gcc version.c -lcurl
 // libcurl/7.64.1

// gcc version.c `pkg-config --cflags --libs libcurl`
// libcurl/7.72.0


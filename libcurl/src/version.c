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
    printf( "LIBCURL_VERSION: %s \n",  LIBCURL_VERSION );
    printf("curl_version: %s \n", curl_version() );

    return EXIT_SUCCESS;
}


// gcc version.c -lcurl
// LIBCURL_VERSION: 7.64.1 
// curl_version: libcurl/7.64.1 SecureTransport (LibreSSL/2.8.3) zlib/1.2.11 nghttp2/1.39.2 

// gcc version.c `pkg-config --cflags --libs libcurl`
// LIBCURL_VERSION: 7.73.0 
// curl_version: libcurl/7.73.0 SecureTransport zlib/1.2.11 


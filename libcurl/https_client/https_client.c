/**
 * https_client.c
 * 2020-07-01 K.OHWADA
 */

// Simple HTTPS Client

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "https_client.h"


/**
 * main
 */
int main(int argc, char *argv[])
{
    const size_t BUFSIZE = 256;
    char url[BUFSIZE];

    char *host = "example.com";

    bool is_verify = true;

  if(argc == 3) {
      	host = argv[1];
      	is_verify = (bool)atoi(argv[2]);
  } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] \n",  argv[0] );
    }

    snprintf(url, BUFSIZE, "https://%s", (char *)host );

    printf("%s \n", host);
    printf("%s \n", url);
    printf("is_verify: %d \n", is_verify);

    bool ret = https_client((char *)url,  is_verify);
    if(!ret){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;;
}


// <title>Example Domain</title>


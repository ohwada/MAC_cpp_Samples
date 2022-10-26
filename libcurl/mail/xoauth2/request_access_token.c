/**
 * request_access_token.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include "access_token.h"


/**
 *  main
 */
int main(void)
{

    const size_t BUFSIZE = 1024;
    char access_token[BUFSIZE];
    char error[BUFSIZE];

    bool is_verbose = true;

    bool ret = getAccessToken(
    (char *)access_token, (char *)error, is_verbose);

    if(!ret){
        fprintf(stderr, "error: %s \n", error);
        return EXIT_FAILURE;
    }

    printf("\n access_token \n");
    printf("%s \n", access_token);

    return EXIT_SUCCESS;
}

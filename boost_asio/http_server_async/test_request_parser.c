/**
 * test_request_parser.c
 * 2022-06-01 K.OHWADA
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include"request_parser.h"


/**
 * main
 */
int main()
{
    const size_t BUFSIZE = 128;
    char path1[BUFSIZE];
    char path2[BUFSIZE];

    char* request1 = (char *)"GET / HTTP/1.1";
    char* request2 = (char *)"GET /abc HTTP/1.1";

    parse_path(request1,  (char *)path1);

    printf("path1: %s \n", path1);

    assert( strcmp(path1, "/") == 0);

    parse_path(request2,  (char *)path2);

    printf("path2: %s \n", path2);

    assert( strcmp(path2, "/abc") == 0);

    printf("successful \n");

    return 0;
}
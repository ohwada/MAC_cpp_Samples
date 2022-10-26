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
    char name[BUFSIZE];

    char* query = (char *)"name=baboon.png";

    parse_query(query, (char *)name );

    printf("name: %s \n", name);

    assert( strcmp(name, "baboon.png") == 0);

    printf("successful \n");

    return 0;
}
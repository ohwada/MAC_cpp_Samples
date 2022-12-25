/**
 * test_ws_request_parser.c
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../ws_server/ws_request_parser.h"


/**
 * main
 */
int main(int argc, char* argv[])
{
    char *text =
"Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n";

   char *expect = 
"dGhlIHNhbXBsZSBub25jZQ==";

    char seckey[100];

    parse_seckey(text,  (char *)seckey);

    printf("seckey: %s \n", seckey);

    assert( strcmp(seckey, expect) == 0);

    printf("successful \n");

    return 0;
}


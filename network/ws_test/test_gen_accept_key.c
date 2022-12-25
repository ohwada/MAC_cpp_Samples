/**
 * test_gen_accept_key.c
 * 2022-10-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../ws_server/ws_response_builder.h"


/**
 * main
 */
int main()
{

    char seckey[] = 
"dGhlIHNhbXBsZSBub25jZQ==";

    char expect[] =
"s3pPLMBiTxaQ9kYGzzhZRbK+xOo="; 

    char accept_key[100];

    gen_accept_key( (char *)seckey, (char* )accept_key);

    printf("accept_key: %s \n", accept_key);

    assert( strcmp(accept_key, expect) == 0 );

    printf("successful \n");

    return 0;
}

// accept_key: s3pPLMBiTxaQ9kYGzzhZRbK+xOo= 
// successful 


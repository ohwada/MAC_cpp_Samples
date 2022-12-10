/**
 * sha512.c
 * 2022-06-01 K.OHWADA
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <openssl/sha.h>
#include "hex.h"


/**
 * gen_sha512
 */

void gen_sha512(char* message, unsigned char* digest)
{
	SHA512_CTX ctx;
// initialize the context
	SHA512_Init(&ctx);
// input message
	SHA512_Update(&ctx, message, sizeof(message)); 
// output to digest
	SHA512_Final(digest, &ctx);
}


/**
 * dump_digest
 */
void dump_digest(unsigned char* digest, size_t size)
{
	for (int i = 0; i < size; i++) {
		printf("%x", digest[i]);
	}
	printf("\n");
}


/**
 * main
 */
int main(int argc, char *argv[])
{
	char message[] = "Sample Message";

    char* expect = 
"43ceac64a4ef3fa83881a86c7306ade5d05641051c7a46fd2a72bcb5002f4ae50e6436816c2d861bec9e7c641a6ecb0e38f51b86336ca51baccf54eef71c2019";

	unsigned char digest[SHA512_DIGEST_LENGTH];

	printf("%s\n", message);
	
	gen_sha512(message, digest);

    char* hex = bin2hex( (char *)digest, SHA512_DIGEST_LENGTH);

    printf("%s \n", hex);

   assert( strcmp(hex, expect) == 0);

    free(hex);

    printf("succesful \n");


    return 0;
}

//Sample Message
//d817b3c71245aa42b7ad6a19c812efe163bfb8de34fb031f64e24c1d18821

/**
 * sha256.c
 * 2022-06-01 K.OHWADA
 */

// refeence : https://blog.takuchalle.dev/post/2019/06/07/sha256_clang/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <openssl/sha.h>
#include "hex.h"


/**
 * gen_sha1
 */
void gen_sha1(char* message, unsigned char* digest)
{
	SHA_CTX ctx;
// initialize the context
	SHA1_Init(&ctx);
// input message
	SHA1_Update(&ctx, message, sizeof(message)); 
// output to digest
	SHA1_Final(digest, &ctx);
}


/**
 * main
 */
int main(int argc, char *argv[])
{
	char message[] = "Sample Message";

    char* expect = "7852df968e6cbb0921bceba47735fe0a2a987ae0";

    unsigned char digest[SHA_DIGEST_LENGTH];

	printf("%s\n", message);
	
	gen_sha1(message, digest);

    char* hex = bin2hex( (char *)digest, SHA_DIGEST_LENGTH);

    printf("%s \n", hex);

    assert( strcmp(hex, expect) == 0);

    free(hex);

    printf("succesful \n");

    return 0;
}

// Sample Message
// 7852df968e6cbb921bceba47735fea2a987ae0


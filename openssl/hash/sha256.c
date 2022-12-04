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
 * gen_sha256
 */

void gen_sha256(char* message, unsigned char* digest)
{
	SHA256_CTX ctx;
// initialize the context
	SHA256_Init(&ctx);
// input message
	SHA256_Update(&ctx, message, sizeof(message)); 
// output to digest
	SHA256_Final(digest, &ctx);
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
"d817b3c71245aa42b7ad6a19c812efe163bf0b8de34fb0031f640e24c1d18821";

	unsigned char digest[SHA256_DIGEST_LENGTH];

	printf("%s\n", message);
	
	gen_sha256(message, digest);

    char* hex = bin2hex( (char *)digest, SHA256_DIGEST_LENGTH);

    printf("%s \n", hex);

   assert( strcmp(hex, expect) == 0);

    free(hex);

    printf("succesful \n");


    return 0;
}

//Sample Message
//d817b3c71245aa42b7ad6a19c812efe163bfb8de34fb031f64e24c1d18821

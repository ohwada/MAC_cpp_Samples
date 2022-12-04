// md5.c
// https://a4dosanddos.hatenablog.com/entry/2015/03/01/191730

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <openssl/md5.h>
#include "hex.h"


/**
 * gen_md5
 */
void gen_md5(char* message, unsigned char* digest)
{
	MD5_CTX ctx;
// initialize the context
	MD5_Init(&ctx);
// input message
	MD5_Update(&ctx, message, sizeof(message)); 
// output to digest
	MD5_Final(digest, &ctx);
}


/**
 * main
 */
int main()
{
	char message[] = "Sample Message";

    char* expect = "c8b062d07ca4bbf53ccc5c27fff3f25d";

	unsigned char digest[MD5_DIGEST_LENGTH];

	printf("%s\n", message);
	
	gen_md5(message, digest);

    char* hex = bin2hex( (char *)digest, MD5_DIGEST_LENGTH);

    printf("%s \n", hex);

    assert( strcmp(hex, expect) == 0);

    free(hex);

    printf("succesful \n");

    return 0;
}

// Sample Message
// c8b062d07ca4bbf53ccc5c27fff3f25d 


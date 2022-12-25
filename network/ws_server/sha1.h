/**
 * sha1.h
 * 2022-06-01 K.OHWADA
 */

#include <openssl/sha.h>

// prototype
void gen_sha1(char* message,  size_t msg_size, unsigned char* digest);


/**
 * gen_sha1
 */
void gen_sha1(char* message, size_t msg_size, unsigned char* digest)
{
	SHA_CTX ctx;
// initialize the context
	SHA1_Init(&ctx);
// input message
	SHA1_Update(&ctx, message, msg_size); 
// output to digest
	SHA1_Final(digest, &ctx);
}


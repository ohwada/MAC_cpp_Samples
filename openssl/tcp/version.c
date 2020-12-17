/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// display version

#include <stdio.h>
#include <stdlib.h>
#include <openssl/opensslv.h>
#include <openssl/ssl.h>

/**
 * main
 */
int main(void)
{

    printf("OPENSSL_VERSION_TEXT: %s \n", OPENSSL_VERSION_TEXT );

    printf("SSL_version_str: %s \n", SSL_version_str );

    return EXIT_SUCCESS;
}


// OPENSSL_VERSION_TEXT: OpenSSL 1.1.1h  22 Sep 2020 
// SSL_version_str: OpenSSL 1.1.1h  22 Sep 2020 



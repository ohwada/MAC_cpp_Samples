#pragma once
/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for ssl server

// reference : https://wiki.openssl.org/index.php/Simple_TLS_Server

#include <openssl/ssl.h>
#include <openssl/err.h>
#include "ssl_write_read.h"


// prototype
void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX *create_context(void);
bool  configure_context(SSL_CTX *ctx, char *file_cert, char *file_key );
bool ssl_accept_sockfd(SSL *ssl, int sockfd_client);


/**
 * init_openssl
 */
void init_openssl(void)
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
}


/**
 * cleanup_openssl
 */
void cleanup_openssl(void)
{
    EVP_cleanup();
}


/**
 *  create_context
 */
SSL_CTX *create_context(void)
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
	    perror("Unable to create SSL context");
	    ERR_print_errors_fp(stderr);
	    return NULL;
    }

    return ctx;
}


/**
 *   configure_context
 */
bool  configure_context(SSL_CTX *ctx, char *file_cert, char *file_key )
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

//* Set cert file
int ret1 = SSL_CTX_use_certificate_file(ctx, file_cert, SSL_FILETYPE_PEM);
    if (ret1 <= 0) {
        ERR_print_errors_fp(stderr);
	    return false;
    }

//  Set the key file
int ret2 = SSL_CTX_use_PrivateKey_file(ctx, file_key, SSL_FILETYPE_PEM);
    if (ret2 <= 0 ) {
        ERR_print_errors_fp(stderr);
	    return false;
    }

    return true;
}


/**
 *  ssl_accept_sockfd
 */
bool ssl_accept_sockfd(SSL *ssl, int sockfd_client)
{

    int ret1 = SSL_set_fd(ssl, sockfd_client);
    if(ret1 != 1){
            ERR_print_errors_fp(stderr);
            return false;
    }

    int ret2 = SSL_accept(ssl);
    if (ret2 != 1) { 
            ERR_print_errors_fp(stderr);
           return false;
    }

    return true;
}


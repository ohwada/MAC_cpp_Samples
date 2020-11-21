#pragma once
/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for ssl server

// reference : https://wiki.openssl.org/index.php/Simple_TLS_Server

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


// prototype
int create_socket(int port);
void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX *create_context(void);
bool  configure_context(SSL_CTX *ctx, char *file_cert, char *file_key );


/**
 * create_socket
 */
int create_socket(int port)
{
    int sfd;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

// create socet file descriptor
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
	    perror("Unable to create socket");
	    return -1;
    }

    int ret1 = bind( sfd, (struct sockaddr*)&addr, sizeof(addr) );
    if (ret1 < 0) {
	    perror("Unable to bind");
	    return -1;
    }

    const int backlog = 1;
    int ret2 = listen( sfd, backlog );
    if (ret2 < 0) {
	    perror("Unable to listen");
	    return -1;
    }

    return sfd;
}


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


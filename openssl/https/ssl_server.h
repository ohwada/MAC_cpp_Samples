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
bool https_server(int port, char *response, char *file_cert, char *file_key);
void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX *create_context(void);
bool  configure_context(SSL_CTX *ctx, char *file_cert, char *file_key );
bool ssl_accept_sockfd(SSL *ssl, int sockfd_client);



/**
 * https_server
 */
bool https_server(int port, char *response, char *file_cert, char *file_key)
{

// read write buffer
     const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];
    char read_buf[BUFSIZE];

    char error[100];

    int sockfd_listen;
    int sockfd_client;
    int backlog = 1;

    SSL_CTX *ctx;
    SSL *ssl;

    init_openssl();

    ctx = create_context();
    if(!ctx){
        return false;
    }

    bool  ret1 = configure_context(ctx, file_cert, file_key );
    if(!ret1){
        return false;
    }

    sockfd_listen =  tcp_socket_listen_port( port,  backlog, (char *)error );

    if( sockfd_listen < 0){
        fprintf(stderr, "socket: %s \n", error);
        return false;

    }
    
    printf("listen port: %d \n", port);

    ssl = SSL_new(ctx);
    if(!ssl){
        ERR_print_errors_fp(stderr);
        return false;
    }

    bool is_verboce = true;

    bool is_error = false;

/* Handle connections */
while(1) 
{

        sockfd_client = tcp_accept(sockfd_listen, (char *)error, is_verboce );
        if (sockfd_client < 0) {
            fprintf(stderr, "accept: %s \n", error);
             is_error = true;
            goto end;
        }

    bool ret2 = ssl_accept_sockfd( ssl, sockfd_client);

        if(!ret2){
            fprintf(stderr, "ssl accept error");
            is_error = true;
            goto end;
        }


    int read_size = ssl_read( ssl, read_buf, BUFSIZE);

    if( read_size > 0 ){
        printf("%s\n", read_buf);
    } else if( read_size < 0 ){
        is_error = true;
        goto end;
    }

    bool ret4 = ssl_write( ssl, response );
         if (!ret4) { 
            is_error = true;
            goto end;
        }       

        close(sockfd_client);

} // while


end:
    if(sockfd_client){
        close(sockfd_listen);
    }

    if(sockfd_client){
        close(sockfd_client);
    }

    if(ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }

    if(ctx){
        SSL_CTX_free(ctx);
    }

    cleanup_openssl();
	ERR_free_strings();

    cleanup_openssl();
	ERR_free_strings();

    if(is_error){
        return false;
    }

    return true;
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

// use ECHD( Elliptic-curve Diffie–Hellman)
    SSL_CTX_set_ecdh_auto(ctx, 1);

//* Set cert file
int ret1 = SSL_CTX_use_certificate_file( ctx, file_cert, SSL_FILETYPE_PEM );
    if (ret1 <= 0) {
        ERR_print_errors_fp(stderr);
	    return false;
    }

//  Set the key file
int ret2 = SSL_CTX_use_PrivateKey_file( ctx, file_key, SSL_FILETYPE_PEM );
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


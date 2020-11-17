#pragma once
/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for ssl

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


// prototype
bool connect_ssl( SSL *ssl, int socketfd);
bool send_ssl(SSL *ssl, char *data);
bool print_recv_ssl(SSL *ssl);


/**
 * connect_ssl
 */
bool connect_ssl( SSL *ssl, int socketfd)
{

    int ssl_ret1 = SSL_set_fd(ssl, socketfd);

    if(ssl_ret1 != 1){
        ERR_print_errors_fp(stderr);
        return false;
    }

    int ssl_ret2 = SSL_connect(ssl);

    if(ssl_ret2 != 1){
         ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}


/**
 * send_ssl
 */
bool send_ssl(SSL *ssl, char *data)
{

    int write_size = SSL_write(ssl, data, strlen(data) );

    if(write_size <= 0) {
         ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}


/**
 * print_recv_ssl
 */
bool print_recv_ssl(SSL *ssl)
{

    const size_t BUFSIZE = 256;
    char response[BUFSIZE];

    int read_size;

    bool is_error = false;

    while(1) 
    {

        read_size = SSL_read(ssl, response, BUFSIZE);

        if( read_size > 0 ) {
            // success
            printf("%s", response);
         } else if (read_size == 0) {
            // recv end
            break;
        } else {
            // error
            is_error = true;
            ERR_print_errors_fp(stderr);
            break;
        }

    } // while

    return !is_error;
}




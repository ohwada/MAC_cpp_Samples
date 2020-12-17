#pragma once
/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for SSL write read 

#include <stdbool.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


// prototype
bool ssl_write(SSL *ssl, char *data);
bool print_ssl_read(SSL *ssl);
int ssl_read(SSL *ssl, char *buf, int bufsize);


/**
 * ssl_write
 */
bool ssl_write(SSL *ssl, char *data)
{

    int write_size = SSL_write(ssl, data, strlen(data) );

    if(write_size <= 0) {
         ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}


/**
 * print_ssl_read
 */
bool print_ssl_read(SSL *ssl)
{

    const char CHAR_NULL = '\0';

    const size_t BUFSIZE = 256;
    char buf[BUFSIZE];

    bool is_error = false;

    while(1) 
    {

// zero clear
    memset(buf, 0, BUFSIZE );

        int size = SSL_read(ssl, (char *)buf, (BUFSIZE - 1) );

        if( size > 0 ) {
            // null terminated string
            buf[size] = CHAR_NULL;
            printf("%s", buf);
         } else if (size == 0) {
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


/**
 * ssl_read
 */
int ssl_read(SSL *ssl, char *buf, int bufsize)
{

    const char CHAR_NULL = '\0';


// zero clear
    memset(buf, 0, bufsize );

        int size = SSL_read(ssl, (char *)buf, (bufsize - 1) );

        if( size > 0 ) {
            // null terminated string
            buf[size] = CHAR_NULL;
         } else if (size < 0) {
            // error
            ERR_print_errors_fp(stderr);
        }

    return size;
}



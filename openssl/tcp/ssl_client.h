#pragma once
/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// function for SSL Client

#include <openssl/ssl.h>
#include <openssl/err.h>
#include "ssl_write_read.h"


// prototype
bool connect_ssl( SSL *ssl, int socketfd);


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


/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// connect HTTPS srver using BIO_new_ssl_connect

// gcc bio_new_ssl_connect.c  `pkg-config --cflags --libs openssl` 

// reference : https://www.openssl.org/docs/man1.0.2/man3/BIO_new_ssl_connect.html


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <openssl/ssl.h>
#include <openssl/err.h>
#include "bio_func.h"
#include "http_build.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char *host = "example.com";

    if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [host] \n",  argv[0] );
    }

// build url
    const size_t URL_SIZE = 100;
    char url[URL_SIZE];

    build_url((char *)host, PORT_HTTPS, (char *)url, URL_SIZE);

    fprintf(stderr, "url: %s \n", url);



BIO *sbio;
 SSL_CTX *ctx;
 SSL *ssl;

sbio = NULL;
ctx = NULL;
ssl =NULL;


// ssl setting
 ERR_load_crypto_strings();
 ERR_load_SSL_strings();
 OpenSSL_add_all_algorithms();

 /* We would seed the PRNG here if the platform didn't
  * do it automatically
  */

    ctx = SSL_CTX_new( SSLv23_client_method() );
    if (!ctx) {
            fprintf(stderr, "SSL_CTX_new failed \n");
            ERR_print_errors_fp(stderr);
            goto label_error;
    }


 /* We'd normally set some stuff like the verify paths and
  * mode here because as things stand this will connect to
  * any server whose certificate is signed by any CA.
  */

    sbio = BIO_new_ssl_connect(ctx);
    if (!sbio) {
        fprintf(stderr, "BIO_new_ssl_connect failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }

    long ret1 = BIO_get_ssl(sbio, &ssl);

     if(ret1 != 1) {
        fprintf(stderr, "BIO_get_ssl failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }

     if(!ssl) {
        fprintf(stderr, "BIO_get_ssl failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }

 /* Don't want any retries */
    long ret2 = SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    if( ret2 != SSL_MODE_AUTO_RETRY ){
            fprintf(stderr, "SSL_set_mode failed \n");
            ERR_print_errors_fp(stderr);
            goto label_error;
    }

 /* We might want to do other things with ssl here */

    long ret3 = BIO_set_conn_hostname(sbio, url);
    if(ret3 != 1){            
            fprintf(stderr, "BIO_set_conn_hostname failed \n");
            ERR_print_errors_fp(stderr);
            goto label_error;
    }

    int ret4 = BIO_do_connect(sbio);
    if(ret4 != 1) {
            fprintf(stderr, "BIO_do_connect failed \n");
            ERR_print_errors_fp(stderr);
            goto label_error;
    }

    long ret5 = BIO_do_handshake(sbio);
    if(ret5 != 1) {
        fprintf(stderr, "BIO_do_handshake failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }


// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", request);


// send request
    bool ret6 = send_bio( sbio, (char *)request );
    if(!ret6){
        fprintf(stderr, "send_bio failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }

// recv response
    bool ret7 = print_recv_bio( sbio );
    if(!ret7){
        fprintf(stderr, "print_recv_bio failed \n");
        ERR_print_errors_fp(stderr);
        goto label_error;
    }


// close and release BIO
    if(sbio){
        BIO_free_all(sbio);
    }

    ERR_free_strings();

   fprintf(stderr, "sucessful \n");

    return EXIT_SUCCESS;


//  --- error ---
label_error:

    if(sbio){
        BIO_free_all(sbio);
    }

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;

}

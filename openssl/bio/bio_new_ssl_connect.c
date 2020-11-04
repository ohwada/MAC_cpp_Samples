/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// connect HTTPS srver using BIO_new_ssl_connect

// gcc bio_new_ssl_connect.c  `pkg-config --cflags --libs libcrypto` 

// reference : https://www.openssl.org/docs/man1.0.2/man3/BIO_new_ssl_connect.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
 #include <openssl/ssl.h>
 #include <openssl/evp.h>
#include <openssl/err.h>


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


    const size_t URL_SIZE = 100;
    char url[URL_SIZE];

    const int PORT = 443;

    snprintf(url, URL_SIZE, "%s:%d", (char *)host, PORT);


BIO *sbio;
 SSL_CTX *ctx;
 SSL *ssl;


 ERR_load_crypto_strings();
 ERR_load_SSL_strings();
 OpenSSL_add_all_algorithms();

 /* We would seed the PRNG here if the platform didn't
  * do it automatically
  */

 ctx = SSL_CTX_new(SSLv23_client_method());

 /* We'd normally set some stuff like the verify paths and
  * mode here because as things stand this will connect to
  * any server whose certificate is signed by any CA.
  */

    sbio = BIO_new_ssl_connect(ctx);
    if (!sbio) {
        // failed
        fprintf(stderr, "BIO_new_ssl_connect faild: %s \n", url);
        return EXIT_FAILURE;
    }

    BIO_get_ssl(sbio, &ssl);
     if(!ssl) {
        fprintf(stderr, "Can't locate SSL pointer\n");
        return EXIT_FAILURE;
    }

 /* Don't want any retries */
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

 /* We might want to do other things with ssl here */

    BIO_set_conn_hostname(sbio, url);

    if(BIO_do_connect(sbio) <= 0) {
            fprintf(stderr, "Error connecting to server\n");
            ERR_print_errors_fp(stderr);
            return EXIT_FAILURE;
    }

    if(BIO_do_handshake(sbio) <= 0) {
        fprintf(stderr, "Error establishing SSL connection\n");
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }


// create GET request 
    const size_t BUFSIZE = 100;
    char buf[100];
    char request[500];

    strcpy(request, "GET / HTTP/1.1\r\n");

    strcat(request, "Accept: */* \r\n");

    snprintf(buf, BUFSIZE, "Host: %s\r\n", (char *)host ); 
    strcat(request, buf); 

   strcat(request, "Connection: close\r\n\r\n"); 

    fprintf(stderr, "%s \n", request);


// calculate request length
  int request_len = strlen(request);


// write request
  int ret1 = BIO_write(sbio, request, request_len); 
    fprintf(stderr, "BIO_write: %d \n", ret1);


    const size_t RESPONSE_SIZE = 1024;
    char response[RESPONSE_SIZE ];
    int read_len = RESPONSE_SIZE -1;
    int len;


// resd response
 while((len = BIO_read(sbio, response, read_len)) > 0)
{
        // print response
        printf("%s \n", (char *)response); 

} // while 


// close and release BIO
    BIO_free_all(sbio);


    return EXIT_SUCCESS;
}

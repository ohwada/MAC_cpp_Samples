/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// get certificate chain from server

// similar Feature to the command below
// openssl s_client -connect host:port  -showcerts
// https://www.openssl.org/docs/man1.1.0/man1/s_client.html

// Note:
// this program output der format
// convert to pem format with the following command
// openssl x509 -inform der -in der_file  -outform pem -out pem_name


//  gcc https/get_certs.c `pkg-config --cflags --libs openssl`


#include <stdio.h>
#include <stdlib.h>
#include "tcp_client.h"
#include "http_client.h"
#include "ssl_client.h"
#include "x509_util.h"


// prototype
int verify_callback(int preverify, X509_STORE_CTX* x509_ctx);


/**
 * main
 */
int main(int argc, char **argv)
{
 
    char *host = "www.example.com";

    int port = 443;

    if(argc == 3) {
      	host = argv[1];
       	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] \n",  argv[0] );
    }

    printf("host: %s \n", host);
    printf("port: %d \n", port);


    const int DEPTH = 5;

    int sockfd;
    char error[100];


    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;


  // create socket
    sockfd  = tcp_socket( (char *)error );

    if( sockfd  < 0 ) {
            fprintf(stderr, "socket: %s \n",  error );
            return EXIT_FAILURE;
    }

// connect host
   bool ret1 = tcp_connect_hostname( sockfd, (char *)host,  port , (char *)error );

    if(ret1){
        fprintf(stderr, "tcp_connect to: %s : %d \n", host, port );
    } else {
        fprintf(stderr, "tcp_connect_hostname: %s \n", error );
        goto  label_error;
    }


// SSL connect
    SSL_load_error_strings();

    SSL_library_init();

    ctx = SSL_CTX_new( SSLv23_client_method() );

    if(!ctx){
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }


// https://www.openssl.org/docs/ssl/ctx_set_verify.html
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);

        SSL_CTX_set_verify_depth( ctx, DEPTH );

    ssl = SSL_new(ctx);

    if(!ssl){
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }



   /* No documentation. See the source code for tls.h and s_client.c */
         int res2 = SSL_set_tlsext_host_name(ssl, host );

    if(res2 != 1){
       fprintf(stderr, "SSL_set_tlsext_host_name faild \n");
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }


    bool ret4 = connect_ssl(ssl, sockfd);

   if(ret4){
       // fprintf(stderr, "connect_ssl: %s \n", host);
    } else {
        goto  label_error;
    }



// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(sockfd);

    printf("\n");
   fprintf(stderr, "sucessful \n");

    return EXIT_SUCCESS;


//  --- error ---
label_error:

	if ( ssl) {
        SSL_shutdown(ssl);
		SSL_free(ssl); 
	}

	if (  ctx ) {
		SSL_CTX_free(ctx);
	}

	if (sockfd) {
		close(sockfd);
	}

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;

}


/**
 * verify_callback
 */
int verify_callback(int preverify, X509_STORE_CTX* x509_ctx)
{

    X509* cert = X509_STORE_CTX_get_current_cert(x509_ctx);

    if(!cert){
        ERR_print_errors_fp(stderr);
        return 1;
    }

   int depth = X509_STORE_CTX_get_error_depth(x509_ctx);



    char subject[100];
    char issuer[100];
    char file[100];
    char error[100];
    bool ret1 = get_x509_subject_name( cert,  (char *)subject );

    if(!ret1){
        return 0;
    }

    bool ret2 = get_x509_issuer_name( cert,  (char *)issuer );

    if(!ret2){
        return 0;
    }


    printf("\n");
    printf("depth: %d \n", depth);
    printf("Subject: %s \n", subject);
    printf("Issuer: %s \n", issuer);

    bool ret3 = save_x509_to_der( cert,  subject );

    return 1;
}

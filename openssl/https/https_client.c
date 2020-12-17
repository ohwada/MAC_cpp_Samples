/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS Client without server certification verification

//  gcc https/https_client.c `pkg-config --cflags --libs openssl` -o client

// reference : http://x68000.q-e-d.net/~68user/net/ssl-1.html


#include <stdio.h>
#include <stdlib.h>
#include "tcp_client.h"
#include "http_client.h"
#include "ssl_client.h"



/**
 * main
 */
int main(int argc, char **argv)
{

    char* host = "example.com";
    int port = 443;


    if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
    } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port]  \n",  argv[0] );
    }

    printf("host: %s \n", host);
    printf("port: %d \n", port);


    char request[500];
    char error[100];

// create GET request 
    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );


    int sockfd;

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


    ssl = SSL_new(ctx);

    if(!ssl){
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }


    bool ret2 = connect_ssl(ssl, sockfd);

   if(ret2){
       fprintf(stderr, "connect_ssl: %s \n", host);
    } else {
        goto  label_error;
    }


// send request
    bool ret3 = ssl_write(ssl, (char *)request );

   if(!ret3){
        goto  label_error;
    }

// recieve response
    bool ret4 = print_ssl_read(ssl);

   if(!ret4){
        goto  label_error;
    }

// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(sockfd);

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


// Conntect to "example.com
// HTTP/1.1 200 OK
// <title>Example Domain</title>


/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTPS Server
// return fixed prepared response

//  gcc https/https_server.c `pkg-config --cflags --libs openssl` -o server

// reference : https://blog.sarabande.jp/post/82087204080


#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include "tcp_server.h"
#include "ssl_server.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    const char FILE_CERT[] = "certs/localhost_cert.pem";

    const char FILE_KEY[] = "certs/localhost_key.pem";

    const char TITLE[] = "openssl demo";

    const char HEADLINE[] = "openssl HTTPS Server demo";


    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];
    char read_buf[BUFSIZE];
    char html[BUFSIZE];
    char response[BUFSIZE];


    int port = 8081;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

    printf("port: %d \n",  port );


// build response
    build_html( (char *)TITLE, (char *)HEADLINE, (char *)html );

    build_response( (char *)html, (char *)response);

    printf("%s \n", response);


    int sockfd_listen;
    int sockfd_client;
    int backlog = 1;

    SSL_CTX *ctx;
    SSL *ssl;

    char error[100];


    init_openssl();

    ctx = create_context();
    if(!ctx){
        return EXIT_FAILURE;
    }

    bool  ret1 = configure_context(ctx, (char *)FILE_CERT, (char *)FILE_KEY );
    if(!ret1){
        return EXIT_FAILURE;
    }

    sockfd_listen =  tcp_socket_listen_port( port,  backlog, (char *)error );

    if( sockfd_listen < 0){
        fprintf(stderr, "socket: %s \n", error);
        return EXIT_FAILURE;
    }
    
    printf("listen port: %d \n", port);

    ssl = SSL_new(ctx);
    if(!ssl){
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }

    bool is_verboce = true;


/* Handle connections */
while(1) 
{

        sockfd_client = tcp_accept(sockfd_listen, (char *)error, is_verboce );
        if (sockfd_client < 0) {
            fprintf(stderr, "accept: %s \n", error);
            goto label_error;
        }

    bool ret2 = ssl_accept_sockfd( ssl, sockfd_client);

        if(!ret2){
         fprintf(stderr, "ssl accept error");
            goto label_error;
        }


    int read_size = ssl_read( ssl, read_buf, BUFSIZE);

    if( read_size > 0 ){
        printf("%s\n", read_buf);
    } else if( read_size < 0 ){
        goto label_error;
    }

    bool ret4 = ssl_write( ssl, response );
         if (!ret4) { 
            goto label_error;
        }       

        close(sockfd_client);

} // while


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

    return EXIT_SUCCESS;


label_error:

    if(ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }

    if(ctx){
        SSL_CTX_free(ctx);
    }

    cleanup_openssl();
	ERR_free_strings();

    if(sockfd_client){
            close(sockfd_client);
    }

    if(sockfd_listen){
        close(sockfd_listen);
    }

    return EXIT_FAILURE;
}


/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// SSL Echo Server
// Echo back the received data as it is

//  gcc tcp/echo_server.c `pkg-config --cflags --libs openssl` -o    server

// reference : https://wiki.openssl.org/index.php/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcp_server.h"
#include "ssl_server.h"
#include "echo_port.h"


/**
 * main
 */
int main(void)
{

    const char FILE_CERT[] = "cert/localhost_cert.pem";

    const char FILE_KEY[] = "cert/localhost_key.pem";

    const size_t BUFSIZE = 1024;
    char write_buf[BUFSIZE];
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
        return EXIT_FAILURE;
    }

    bool  ret1 = configure_context(ctx, (char *)FILE_CERT, (char *)FILE_KEY );
    if(!ret1){
        return EXIT_FAILURE;
    }

    sockfd_listen = tcp_socket_listen_port( PORT, backlog, 
    (char *)error );
    if( sockfd_listen < 0){
        return EXIT_FAILURE;
    }

printf("listen pot: %d \n", PORT);

    ssl = SSL_new(ctx);
    if(!ssl){
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }

    bool is_verboce = true;

/* Handle connections */
while(1) 
{
        sockfd_client = tcp_accept( sockfd_listen, (char *)error, is_verboce );


        if (sockfd_client < 0) {
            fprintf(stderr, "tcp accept error");
            goto label_error;
        }

    bool ret2 = ssl_accept_sockfd( ssl, sockfd_client);

        if(!ret2){
         fprintf(stderr, "ssl accept error");
            goto label_error;
        }


while(1)
{
        int read_size = ssl_read( ssl, (char *)read_buf, BUFSIZE);
         if ( read_size > 0 ) {
            printf("r: %s \n", read_buf); 
         } else if ( read_size == 0 ) {
            printf("maybe sockfd_client sockfd_listenet close \n"); 
            break;
        } else {
            fprintf(stderr, "read error \n"); 
            break;
        }   

// echo back
strcpy(write_buf, read_buf);

        bool ret4 = ssl_write(ssl, (char *)write_buf );
        //int ret4 = SSL_write(ssl, REPLY, strlen(REPLY));
         if ( !ret4  ) { 
                 // fprintf(stderr, "write error \n"); 
                break;
        }
       
} // while

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sockfd_client);

} // while

    close(sockfd_listen);
    SSL_CTX_free(ctx);
    cleanup_openssl();
	ERR_free_strings();

    printf("successful \n"); 

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

    printf("failed \n"); 

    return EXIT_FAILURE;
}


/// listen pot: 4433 



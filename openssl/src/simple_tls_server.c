/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// Simple TLS Server
//  gcc simple_tls_server.c `pkg-config --cflags --libs openssl` -o simple

// reference : https://wiki.openssl.org/index.php/Simple_TLS_Server

#include <stdio.h>
#include <stdlib.h>
#include "ssl_server.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    const char FILE_CERT[] = "cert/server.pem";

    const char FILE_KEY[] = "cert/server.key";

    const int PORT = 4433;

    const char REPLY[] = "Simple TLS Server \n";

    int sock;
    int client;

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

    sock = create_socket( PORT );
    if( sock < 0){
        return EXIT_FAILURE;
    }

    ssl = SSL_new(ctx);
    if(!ssl){
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr;
    uint len = sizeof(addr);

/* Handle connections */
while(1) 
{

        client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept");
            goto label_error;
        }

        printf("connected from: %s : %d \n", inet_ntoa(addr.sin_addr), 
        ntohs(addr.sin_port) );

        int ret2 = SSL_set_fd(ssl, client);
        if(ret2 != 1){
            ERR_print_errors_fp(stderr);
            goto label_error;
        }

        int ret3 = SSL_accept(ssl);
        if (ret3 != 1) { 
            ERR_print_errors_fp(stderr);
           goto label_error;
        }
    
        int ret4 = SSL_write(ssl, REPLY, strlen(REPLY));
         if ( ret4 <= 0 ) { 
            ERR_print_errors_fp(stderr);
        }       

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client);

} // while

    close(sock);
    SSL_CTX_free(ctx);
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

    if(client){
            close(client);
    }

    if(sock){
        close(sock);
    }

    return EXIT_FAILURE;
}


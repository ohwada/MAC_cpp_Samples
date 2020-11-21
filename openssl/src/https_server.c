/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTPS Server
// return fixed prepared response

//  gcc https_server.c `pkg-config --cflags --libs openssl` -o server

// reference : https://blog.sarabande.jp/post/82087204080


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

  char HEADER_FORMAT[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d \r\nConnection: Close\r\n";

  char BODY[] = "<html><head><title>openssl demo</title></head><body><h1>openssl HTTPS Server demo</h1></body></html>";

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];
    char request[BUFSIZE];
    char response[BUFSIZE];

    int port = 8081;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

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

    sock = create_socket( port );
    if( sock < 0){
        return EXIT_FAILURE;
    }

    ssl = SSL_new(ctx);
    if(!ssl){
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }



// response
    snprintf( buf, BUFSIZE, (char *)HEADER_FORMAT, strlen(BODY));

    strcpy( (char *)response, (char *)buf );
    strcat( (char *)response, (char *)BODY );



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
    
    int read_size = SSL_read(ssl, request, BUFSIZE);
    if( read_size > 0 ){
        printf("%s\n", request);
    } else {
        ERR_print_errors_fp(stderr);
    }

        int write_size = SSL_write( ssl, response, strlen(response) );
         if ( write_size <= 0 ) { 
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


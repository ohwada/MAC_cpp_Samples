/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// get web page from Google with HTTPS
// reference : https://qiita.com/edo_m18/items/41770cba5c166f276a83
// https://www.geekpage.jp/programming/linux-network/getaddrinfo-1.php

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/opensslv.h>


/**
 * main
 */
int main(void) 
{

// param
    const char* host = "www.google.com";
    const char *path = "/";
    const int   port = 443;
    const char *service = "https";

    int mysocket;
    struct sockaddr_in server;
    struct addrinfo hints, *res;
    struct in_addr addr;

    SSL *ssl;
    SSL_CTX *ctx;

    const int MSGLEN = 100;
    char msg[MSGLEN];

// version
    fprintf(stderr, "%s \n", (char *)OPENSSL_VERSION_TEXT );


    // get IP address from host name
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = 0;
    if ((err = getaddrinfo(host, service, &hints, &res)) != 0) {
        fprintf(stderr, "Fail to resolve ip address - %d\n", err);
        return EXIT_FAILURE;
    }


// print IP address
    addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
    fprintf(stderr,"ip address : %s \n", inet_ntoa(addr));

    if ((mysocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        fprintf(stderr, "Fail to create a socket.\n");
        return EXIT_FAILURE;
    }

    if (connect(mysocket, res->ai_addr, res->ai_addrlen) != 0) {
        fprintf(stderr, "Connection error.\n");
        return EXIT_FAILURE;
    }

    SSL_load_error_strings();
    SSL_library_init();

    ctx = SSL_CTX_new(SSLv23_client_method());
    ssl = SSL_new(ctx);
    err = SSL_set_fd(ssl, mysocket);
    SSL_connect(ssl);

    fprintf(stderr, "Conntect to %s\n", host);

    snprintf(msg, MSGLEN, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", path, host);

    SSL_write(ssl, msg, strlen(msg));

    const int BUFSIZE = 256;
    char buf[BUFSIZE];
    int read_size;

    do {
        read_size = SSL_read(ssl, buf, BUFSIZE);
        write(1, buf, read_size);
    } while(read_size > 0);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(mysocket);

    return EXIT_SUCCESS;
}

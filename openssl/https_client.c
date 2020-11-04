/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// get web page from HTTP server with HTTPS
// reference : https://blog.sarabande.jp/post/82068392478


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int main(int argc, char **argv)
{

// param
    const char *SERVIVCE = "https";
    const int   PORT = 443;
    const char *PATH = "/";

    char* host = "example.com";

    if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] \n",  argv[0] );
    }


    int mysocket;
    struct sockaddr_in server;
    struct addrinfo hints, *res;
    struct in_addr addr;

    SSL *ssl;
    SSL_CTX *ctx;

    // get IP address from host name
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = 0;
    if ((err = getaddrinfo(host, SERVIVCE, &hints, &res)) != 0) {
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


// create GET request 
    const size_t BUFSIZE = 100;
    char buf[100];
    char request[500];

  snprintf(buf, BUFSIZE, "GET %s HTTP/1.1\r\n", PATH);
  strcpy(request, buf);

  strcat(request, "Accept: */* \r\n");

  snprintf(buf, BUFSIZE, "Host: %s\r\n", (char *)host ); 
  strcat(request, buf); 

   strcat(request, "Connection: close\r\n\r\n"); 

    fprintf(stderr, "%s \n", request);

    SSL_write(ssl, request, strlen(request));

    const int RESPONSE_SIZE = 256;
    char response[RESPONSE_SIZE];
    int read_size;

    do {
        read_size = SSL_read(ssl, response, RESPONSE_SIZE);
        printf("%s", response);
    } while(read_size > 0);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(mysocket);

    return EXIT_SUCCESS;
}


// Conntect to "example.com




/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// simple HTTPS Server 
// using server chain certficate
// return fixed prepared response

//  gcc https/https_server_chain_cert.c `pkg-config --cflags --libs openssl` -o server

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

    const char FILE_CERT[] = "certs/localhost_chain_cert.pem";

    const char FILE_KEY[] = "certs/localhost_key.pem";

    const char TITLE[] = "openssl demo";

    const char HEADLINE[] = "openssl HTTPS Server demo";

    const char DESCRIPTION[] = "server chain certficate";

    int port = 8082;

    if(argc == 2) {
      	port = atoi( argv[1] );
    } else {
        fprintf(stderr, "Usage: %s [port] \n",  argv[0] );
    }

    printf("port: %d \n",  port );


     const size_t BUFSIZE = 1024;
    char html[BUFSIZE];
    char response[BUFSIZE];


// build response
    build_html_desc( (char *)TITLE, (char *)HEADLINE, (char *)DESCRIPTION, (char *)html );

    build_response( (char *)html, (char *)response);

    printf("%s \n", response);

    bool ret = https_server( port, (char *)response, (char *)FILE_CERT, (char *)FILE_KEY );

    if(!ret){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


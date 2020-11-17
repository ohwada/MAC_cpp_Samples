/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// get web page from HTTP server with HTTPS
// reference : http://x68000.q-e-d.net/~68user/net/ssl-1.html

//  gcc https_client.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include "ssl_func.h"
#include "http_socket.h"
#include "http_build.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char* host = "example.com";

    if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] \n",  argv[0] );
    }

    int socketfd;

    SSL_CTX *ctx;
    SSL *ssl;
    ctx = NULL;
    ssl = NULL;

// getaddrinfo
    struct addrinfo *info;
    char error[100];

 bool ret1 = get_addrinfo( (char *)host, (char *)SERVICE_HTTPS,  &info, (char *)error );

   if ( ret1) {
        print_addrinfo( info );
    } else {
        fprintf(stderr, "getaddrinfo: %s \n", error );
        return EXIT_FAILURE;
    }


// print IP addinfos
    char ipaddr[100];

    get_ipaddr_from_addrinfo(info, (char *)ipaddr);

    fprintf(stderr, "ipaddr: %s \n", ipaddr);


// open socket
    bool ret2 = open_socket( info, &socketfd, (char *)error );

    if(ret2){
        fprintf(stderr, "open_socket: %d \n", socketfd);
    } else {
        fprintf(stderr, "open_socket: %s \n", error);
        return EXIT_FAILURE;
    }

// connect socket
    bool ret3 = connect_socket( socketfd, info, (char *)error );

    if(ret3){
        fprintf(stderr, "connect_socket: %d \n", socketfd);
    } else {
        fprintf(stderr, "connect_socket: %s \n", error);
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

    bool ret4 = connect_ssl(ssl, socketfd);

   if(ret4){
       fprintf(stderr, "connect_ssl: %s \n", host);
    } else {
        goto  label_error;
    }


// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );

// send request
    bool ret5 = send_ssl(ssl, (char *)request );

   if(!ret5){
        goto  label_error;
    }

// recieve response
    bool ret6 = print_recv_ssl(ssl);

   if(!ret6){
        goto  label_error;
    }

// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close_socket(socketfd);

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

	if (socketfd) {
		close_socket(socketfd);
	}

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;

}


// Conntect to "example.com




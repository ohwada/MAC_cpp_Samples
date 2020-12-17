/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// SSL Echo Client for SSL Echo server
// send SSL packet continuously every one second

//  gcc tcp/echo_client.c `pkg-config --cflags --libs openssl` -o client

// reference : http://x68000.q-e-d.net/~68user/net/ssl-1.html


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "tcp_client.h"
#include "ssl_client.h"
#include "echo_port.h"


/**
 * main
 */
int main(void)
{

    char HOST[] = "localhost";

   const int MAX_LOOP = 100;

    const unsigned int INTINTERVAL = 1; // 1 sec

    const size_t BUFSIZE = 1024;
    char write_buf[BUFSIZE];
    char read_buf[BUFSIZE];

    char error[100];

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
   bool ret1 = tcp_connect_hostname( sockfd, (char *)HOST,  PORT , (char *)error );

    if(ret1){
        fprintf(stderr, "tcp_connect to: %s : %d \n", HOST, PORT );
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
       fprintf(stderr, "connect_ssl: %s \n", HOST);
    } else {
        goto  label_error;
    }

bool is_error = false;

for(int i=0; i<MAX_LOOP; i++)
{

  snprintf( write_buf, BUFSIZE, "%03d", i );

// send data
    bool ret3 = ssl_write(ssl, (char *)write_buf );

    if(ret3){
        printf("s: %s \n", write_buf);
   } else {
        is_error = true;
        fprintf(stderr, "write error \n");
        break;
    }

// recieve response
int read_size = ssl_read( ssl, (char *)read_buf, BUFSIZE );

    //bool ret4 = print_ssl_read(ssl);

   if(read_size > 0 ){
        printf("r: %s \n", read_buf);
    } else if ( read_size == 0 ) {
            printf("maybe client socket close \n"); 
            break;
   } else {
        is_error = true;
        fprintf(stderr, "read error \n");
        break;
    }

    printf("\n");

    sleep(INTINTERVAL);

  } // for


// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(sockfd);

    if(is_error){
            fprintf(stderr, "failed \n");
            return EXIT_FAILURE;
    }

   printf("sucessful \n");

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

	printf("failed \n");

	return EXIT_FAILURE;

}


// Conntect to "example.com
// HTTP/1.1 200 OK
// <title>Example Domain</title>


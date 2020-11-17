/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */


// obtain server SSL certificate

// reference : https://stackoverflow.com/questions/10578716/obtaining-ssl-certificate-on-windows-using-c

// change log
// modify for posix c

// gcc get_server_cert.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <openssl/x509v3.h> 
#include "http_socket.h"
#include "ssl_func.h"



/**
 * main
 */
int main(int argc,char **argv)
{

    const size_t BUFSIZE = 100;
    char file[BUFSIZE + 1];
    file[BUFSIZE] = '\0';

    char* host = "example.com";

    int port = PORT_HTTPS;

    if(argc == 4) {
      	host = argv[1];
      	port = atoi( argv[2] );
      	strcpy( file, argv[3] );
   }  if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
   } else  if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] [file ] \n",  argv[0] );
    }

    if ( strlen(file) == 0) {
        snprintf( file, BUFSIZE, "%s_%d.pem", host, port );
    }

    printf("host: %s \n",  host );
    printf("port: %d \n",  port );
    printf("file: %s \n",  file );


// open file
    FILE *fp;

    fp = fopen(file, "wb");
    if(!fp){
        fprintf(stderr, "can not open: %s \n",  file );
        return EXIT_FAILURE;
    }


    int socketfd;

    SSL_CTX *ctx;
    SSL *ssl;
    ctx = NULL;
    ssl = NULL;

// getaddrinfo
    struct addrinfo *info;
    char error[100];

 bool ret1 = get_addrinfo( (char *)host, NULL,  &info, (char *)error );

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

// connect host
bool ret3 = connect_host( socketfd, (char *)ipaddr, port, ( char *)error );

    if(ret3){
        fprintf(stderr, "connect_host: %s : %d \n", host, port);
    } else {
        fprintf(stderr, "connect_host: %s \n", error);
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



//handle SNI (server name indication)
// required for Gmail
	int ret4 = SSL_set_tlsext_host_name(ssl, host);
	if(ret4 != 1){
       fprintf(stderr, "SSL_set_tlsext_host_name failed \n" );
		ERR_print_errors_fp(stderr);
		goto  label_error;
	}


    bool ret5 = connect_ssl(ssl, socketfd);

   if(ret5){
       fprintf(stderr, "connect_ssl: %d \n", socketfd );
    } else {
       fprintf(stderr, "connect_ssl failed \n" );
        goto  label_error;
    }

   X509 *cert;
   cert = SSL_get_peer_certificate(ssl);

    if(!cert ){
       fprintf(stderr, "SSL_get_peer_certificate failed \n" );
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }


   int ret6 = PEM_write_X509( fp, cert );
  if(ret6 != 1){
       fprintf(stderr, "PEM_write_X509 failed \n" );
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }

// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close_socket(socketfd);

    fclose(fp);

   printf( "saved to: %s \n", file );

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

    if(fp) {
        fclose(fp);
    }

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;

}

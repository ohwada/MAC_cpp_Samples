/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

//  HTTP Client with server certification verification

//  gcc https/https_client_verify.c `pkg-config --cflags --libs openssl` -o verify

// reference : https://wiki.openssl.org/index.php/SSL/TLS_Client#Verification
// reference : https://www.bit-hive.com/articles/20200407


#include <stdio.h>
#include <stdlib.h>
#include "tcp_client.h"
#include "http_client.h"
#include "ssl_client.h"
#include "x509_util.h"


// prototype
int verify_callback(int preverify, X509_STORE_CTX* x509_ctx);
bool enable_hostname_validation(SSL *ssl, const char *host);


// global
char host[100];


/**
 * main
 */
int main(int argc, char **argv)
{

    char* file_ca = "certs/bundle_ca.pem";

    strcpy(host, "www.example.com");

    int port = 443;


    if(argc == 4) {
        strcpy( host, argv[1] );
      	port = atoi( argv[2] );
      	file_ca = argv[3];
    } else if(argc == 3) {
      	strcpy( host, argv[1]) ;
       	port = atoi( argv[2] );
    } else if(argc == 2) {
      	strcpy( host, argv[1] );
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] [file ca] \n",  argv[0] );
    }

    printf("host: %s \n", host);
    printf("port: %d \n", port);
    printf("file ca: %s \n", file_ca);

    char request[500];
    char error[100];

// create GET request 
    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );


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
   bool ret1 = tcp_connect_hostname( sockfd, (char *)host,  port , (char *)error );

    if(ret1){
        fprintf(stderr, "tcp_connect to: %s : %d \n", host, port );
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


    int res = SSL_CTX_load_verify_locations(ctx, (char *)file_ca, NULL );
    if(res != 1){
        fprintf(stderr, "SSL_CTX_load_verify_locations faild \n");
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }

// https://www.openssl.org/docs/ssl/ctx_set_verify.html
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);

        SSL_CTX_set_verify_depth(ctx, 5);

    ssl = SSL_new(ctx);

    if(!ssl){
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }



// set host in SNI(Server Name Indication) 
// See the source code for tls.h and s_client.c 
         int res2 = SSL_set_tlsext_host_name(ssl, (char *)host );

    if(res2 != 1){
       fprintf(stderr, "SSL_set_tlsext_host_name faild \n");
        ERR_print_errors_fp(stderr);
        goto  label_error;
    }

// host name verification
	bool ret3 = enable_hostname_validation(ssl, host);
	if(!ret3){
		goto  label_error;
	}

    bool ret4 = connect_ssl(ssl, sockfd);

   if(ret4){
       // fprintf(stderr, "connect_ssl: %s \n", host);
    } else {
        goto  label_error;
    }


// send request
    bool ret5 = ssl_write(ssl, (char *)request );

   if(!ret5){
        goto  label_error;
    }

// recieve response
    //bool ret5 = print_ssl_read(ssl);

   //if(!ret5){
        //goto  label_error;
    //}

// close SSL
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    close(sockfd);


    printf("\n");
   fprintf(stderr, "verification sucessful \n");

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

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;

}


/**
 * verify_callback
 */
int verify_callback( int preverify, X509_STORE_CTX* x509_ctx )
{

// preverify:
 // 1 : verification passed
// 0: not passed

    /* For error codes, see http://www.openssl.org/docs/apps/verify.html  */
    
    int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
    int err = X509_STORE_CTX_get_error(x509_ctx);
    
    X509* cert = X509_STORE_CTX_get_current_cert(x509_ctx);

    if(!cert){
        ERR_print_errors_fp(stderr);
        return 0;
    }

    char subject[100];
    char issuer[100];

    bool ret1 = get_x509_subject_name( cert,  (char *)subject );

    if(!ret1){
        return 0;
    }

    bool ret2 = get_x509_issuer_name( cert,  (char *)issuer );

    if(!ret2){
        return 0;
    }


    printf("\n");
    printf("depth: %d \n", depth);
    printf("Subject: %s \n", subject);
    printf("Issuer: %s \n", issuer);


    if(depth == 0) {
        /* If depth is 0, its the server's certificate. Print the SANs */
        printf("Subject Alternative Name \n");
        print_x509_san_names( cert );
    }


    if(preverify == 0)
    {

// error code :    
// https://www.openssl.org/docs/manmaster/man3/X509_STORE_CTX_get_error.html

        if(err == X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)
            fprintf(stdout, "  Error:  X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY\n");
        else if(err == X509_V_ERR_CERT_UNTRUSTED)
            fprintf(stdout, "  Error:  X509_V_ERR_CERT_UNTRUSTED\n");
        else if(err == X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN)
            fprintf(stdout, "  Error:  X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN\n");
        else if(err == X509_V_ERR_CERT_NOT_YET_VALID)
            fprintf(stdout, "  Error:  X509_V_ERR_CERT_NOT_YET_VALID\n");
        else if(err == X509_V_ERR_CERT_HAS_EXPIRED)
            fprintf(stdout, "  Error:  X509_V_ERR_CERT_HAS_EXPIRED\n");
     else if(err == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
            fprintf(stdout, "  Error:  X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT \n");
     else if(err == X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE)
            fprintf(stdout, "  Error:  X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE \n");
        else if(err == X509_V_OK)
            fprintf(stdout, "  Error:  X509_V_OK\n");
        else
            fprintf(stdout, "  Error:  %d\n", err);
            return 0;
    }

    if( depth == 0 ) {
            int ret = X509_check_host(cert, (char *)host, strlen(host),
                     0, NULL);
            if(ret == 1){
               fprintf(stderr, "\n" );
                fprintf(stderr, "X509_check_host ok \n" );
            } else {
                fprintf(stderr, "X509_check_host: %s faild \n", (char*)host );
                return 0;
            }
    }

// return value :
// 1: the verification process is continued.
// 0: the verification process is immediately stopped with "verification failed" state.
#if !defined(NDEBUG)
    return 1;
#else
    return preverify;
#endif
}
    

/**
 * enable_host name validation
*/
bool enable_hostname_validation(SSL *ssl, const char *host)
{

	bool is_error = false;

	X509_VERIFY_PARAM *param;

	param = SSL_get0_param(ssl);

	X509_VERIFY_PARAM_set_hostflags(param, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);

// sets the expected DNS hostname
	int ret = X509_VERIFY_PARAM_set1_host(param, host, 0);

	if ( ret != 1) {
		is_error = true;
		ERR_print_errors_fp(stderr);
	}

	return !is_error;
}


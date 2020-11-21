/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// verify host name of server certificate 

// gcc https_hostname_validation.c `pkg-config --cflags --libs openssl` 

// reference : https://www.bit-hive.com/articles/20200407
// https://wiki.openssl.org/index.php/host_validation



#include <stdio.h>
#include <stdlib.h>
#include <openssl/x509v3.h>
#include <openssl/err.h>
#include "ssl_func.h"
#include "http_socket.h"
#include "http_build.h"


// prototype
int verify_callback(int preverified, X509_STORE_CTX *ctx);
bool enable_hostname_validation(SSL *ssl, const char *host);


/**
 * verify_callback
*/
int verify_callback(int preverified, X509_STORE_CTX *ctx)
{

    const size_t BUFSIZE = 1024;
	char subject[ BUFSIZE + 1];


// get current cert
	X509* cert;

	cert = X509_STORE_CTX_get_current_cert(ctx);
	if (cert == NULL) {
            fprintf(stderr, "X509_STORE_CTX_get_current_cert failed \n" );
		    ERR_print_errors_fp(stderr);
		    return 0;
	}


// get subject name
    X509_NAME *subject_name = X509_get_subject_name(cert);
    if( subject_name == NULL ) {
            fprintf(stderr, "X509_get_subject_name failed \n" );
		    ERR_print_errors_fp(stderr);
		    return 0;
    }


// get ASCII version of subject name
	X509_NAME_oneline( subject_name, (char *)subject, BUFSIZE );

	fprintf(stderr, "debug: %d %s\n", preverified, subject);

	return preverified;
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



/**
 * main
*/
int main(int argc, char **argv)
{

	char *host ="example.com";

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


// connect to host
	bool ret3 = connect_host( socketfd, (char *)ipaddr, PORT_HTTPS,  (char *)error );

    if(ret3){
        fprintf(stderr, "connect to: %s \n", host);
    } else {
        fprintf(stderr, "connect_host: %s \n", error);
        goto  label_error;
    }


// ssl seting
	SSL_load_error_strings();

	SSL_library_init();

	ctx = SSL_CTX_new(TLS_client_method());
	if (!ctx) {
		ERR_print_errors_fp(stderr);
		goto  label_error;
	}


// set the minimum supported protocol
 	int ret4 = SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION); 
	if (ret4 == 0) {
		ERR_print_errors_fp(stderr);
		goto  label_error;
	}


// specifies that the default locations from which CA certificates are loaded should be used. 
	int ret5 = SSL_CTX_set_default_verify_paths(ctx);
	if (ret5 == 0) {
		ERR_print_errors_fp(stderr);
		goto  label_error;
	}


// sets the verification flags for ctx to be mode and specifies the verify_callback function
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);


// create ssl
	ssl = SSL_new(ctx);
	if (!ssl) {
		ERR_print_errors_fp(stderr);
		goto label_error;
	}


// host name verification
	bool ret6 = enable_hostname_validation(ssl, host);
	if(!ret6){
		goto  label_error;
	}


//handle SNI (server name indication)
	int ret7 = SSL_set_tlsext_host_name(ssl, host);
	if(ret7 != 1){
		ERR_print_errors_fp(stderr);
		goto  label_error;
	}





// connect ssl
	bool ret8 = connect_ssl(ssl, socketfd);

   if(ret8){
       fprintf(stderr, "connect_ssl: %d \n", socketfd);
    } else {
        goto  label_error;
    }


// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );

// send request
	bool ret9 = send_ssl(ssl, (char *)request );

	if(!ret9){
        goto  label_error;
	}

// recieve response
    bool ret10 = print_recv_ssl(ssl);

   if(!ret10){
        goto  label_error;
    }


// close ssl
	SSL_shutdown(ssl);
	SSL_free(ssl); 
	SSL_CTX_free(ctx);
	close_socket(socketfd);
	ERR_free_strings();

	fprintf(stderr, "successful \n");

 	return EXIT_SUCCESS;


// ----- error -----
 label_error:

	if (ssl) {
		SSL_free(ssl); 
	}

	if (ctx) {
		SSL_CTX_free(ctx);
	}

	if (socketfd) {
			close_socket(socketfd);
	}

	ERR_free_strings();

	fprintf(stderr, "failed \n");

	return EXIT_FAILURE;
}


// connect to: example.com 
// debug: 1 /C=US/O=DigiCert Inc/CN=DigiCert SHA2 Secure Server CA



/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS Client with server certification verification

//  gcc https/https_client_verify.c `pkg-config --cflags --libs openssl`

// reference : https://wiki.openssl.org/index.php/SSL/TLS_Client#Verification


#include <stdio.h>
#include <stdlib.h>
#include <openssl/x509v3.h>
#include "tcp_client.h"
#include "http_client.h"
#include "ssl_client.h"


// prototype
int verify_callback(int preverify, X509_STORE_CTX* x509_ctx);
void print_cn_name(const char* label, X509_NAME* const name);
void print_san_name(const char* label, X509* const cert);
bool enable_hostname_validation(SSL *ssl, const char *host);


// global
char host[100];


/**
 * main
 */
int main(int argc, char **argv)
{

    char* file_ca = "cert/bundle_ca.pem";

    strcpy( host, "example.com");

    int port = 443;


    if(argc == 4) {
        strcpy( host, argv[1] );
      	port = atoi( argv[2] );
      	file_ca = argv[3];
    } else if(argc == 3) {
      	strcpy( host, argv[1] );
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



   /* No documentation. See the source code for tls.h and s_client.c */
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
int verify_callback(int preverify, X509_STORE_CTX* x509_ctx)
{

    /* For error codes, see http://www.openssl.org/docs/apps/verify.html  */
    
    int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
    int err = X509_STORE_CTX_get_error(x509_ctx);
    
    X509* cert = X509_STORE_CTX_get_current_cert(x509_ctx);
    X509_NAME* iname = cert ? X509_get_issuer_name(cert) : NULL;
    X509_NAME* sname = cert ? X509_get_subject_name(cert) : NULL;
    
    fprintf(stdout, "\n verify_callback (depth=%d)(preverify=%d)\n", depth, preverify);
    
    /* Issuer is the authority we trust that warrants nothing useful */
    print_cn_name("Issuer (cn)", iname);
    
    /* Subject is who the certificate is issued to by the authority  */
    print_cn_name("Subject (cn)", sname);
    
    if(depth == 0) {
        /* If depth is 0, its the server's certificate. Print the SANs */
        print_san_name("Subject (san)", cert);
    }
    
    if(preverify == 0)
    {
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
                fprintf(stderr, "X509_check_host ok \n" );
            } else {
                fprintf(stderr, "X509_check_host: %s faild \n", (char*)host );
                return 0;
            }
    }

#if !defined(NDEBUG)
    return 1;
#else
    return preverify;
#endif
}


/**
 * print_cn_name
 */
void print_cn_name(const char* label, X509_NAME* const name)
{
    int idx = -1, success = 0;
    unsigned char *utf8 = NULL;
    
    do
    {
        if(!name) break; /* failed */
        
        idx = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        if(!(idx > -1))  break; /* failed */
        
        X509_NAME_ENTRY* entry = X509_NAME_get_entry(name, idx);
        if(!entry) break; /* failed */
        
        ASN1_STRING* data = X509_NAME_ENTRY_get_data(entry);
        if(!data) break; /* failed */
        
        int length = ASN1_STRING_to_UTF8(&utf8, data);
        if(!utf8 || !(length > 0))  break; /* failed */
        
        fprintf(stdout, "  %s: %s\n", label, utf8);
        success = 1;
        
    } while (0);
    
    if(utf8)
        OPENSSL_free(utf8);
    
    if(!success)
        fprintf(stdout, "  %s: <not available>\n", label);
}


/**
 * print_san_name
 */
void print_san_name(const char* label, X509* const cert)
{
    int success = 0;
    GENERAL_NAMES* names = NULL;
    unsigned char* utf8 = NULL;
    
    do
    {
        if(!cert) break; /* failed */
        
        names = X509_get_ext_d2i(cert, NID_subject_alt_name, 0, 0 );
        if(!names) break;
        
        int i = 0, count = sk_GENERAL_NAME_num(names);
        if(!count) break; /* failed */
        
        for( i = 0; i < count; ++i )
        {
            GENERAL_NAME* entry = sk_GENERAL_NAME_value(names, i);
            if(!entry) continue;
            
            if(GEN_DNS == entry->type)
            {
                int len1 = 0, len2 = -1;
                
                len1 = ASN1_STRING_to_UTF8(&utf8, entry->d.dNSName);
                if(utf8) {
                    len2 = (int)strlen((const char*)utf8);
                }
                
                if(len1 != len2) {
                    fprintf(stderr, "  Strlen and ASN1_STRING size do not match (embedded null?): %d vs %d\n", len2, len1);
                }
                
                /* If there's a problem with string lengths, then     */
                /* we skip the candidate and move on to the next.     */
                /* Another policy would be to fails since it probably */
                /* indicates the client is under attack.              */
                if(utf8 && len1 && len2 && (len1 == len2)) {
                    fprintf(stdout, "  %s: %s\n", label, utf8);
                    success = 1;
                }
                
                if(utf8) {
                    OPENSSL_free(utf8), utf8 = NULL;
                }
            }
            else
            {
                fprintf(stderr, "  Unknown GENERAL_NAME type: %d\n", entry->type);
            }
        }

    } while (0);
    
    if(names)
        GENERAL_NAMES_free(names);
    
    if(utf8)
        OPENSSL_free(utf8);
    
    if(!success)
        fprintf(stdout, "  %s: <not available>\n", label);
    
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


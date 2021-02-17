/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// Simple S/MIME sign verify example 
// send mail from Jiro to Taro 

// gcc  test_sign_verify.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smime.h"
#include "file_util.h"

bool test_sign_verify( char *sign_input, char *sign_output, char *signer_cert,  char *signer_key, int sign_flags,  char *signer_cacert, STACK_OF(X509) *verify_certs )
{


    char ver_output[100];
    strcpy(ver_output, "verified_");
    strcat(ver_output, sign_output );

    STACK_OF(X509) *sign_certs = NULL;

    bool ret1 = smime_sign( sign_input,  sign_output, signer_cert,  signer_key,  sign_certs,  sign_flags );

    if(ret1) {
        printf("sign successful \n");
        if ( file_exists(sign_output) ) {
            printf("saved: %s \n", sign_output);
        }
    } else {
        printf("sign faild \n");
	    return false;
    }

    int ver_flags = 0;

    bool ret2 = smime_verify( sign_output, ver_output, signer_cacert,ver_certs, ver_flags );

    if(ret2) {
        printf("verify successful \n");
        if ( file_exists(ver_output) ) {
            printf("saved: %s \n", ver_output );
        }
    } else {
        printf("verify faild \n");
	    return false;
    }


    char error[100];

    char *original = file_text_read( sign_input, (char *)error );

    if(!original) {
        printf("file_text_read faild: %s \n", sign_input);
	    return false;
    }

    char *verify = file_text_read( ver_output, (char *)error );

    if(!verify) {
        printf("file_text_read faild: %s \n", ver_output );
	    return false;
    }

    if( strcmp(original, verify) != 0 ) {
        printf("unmatch \n");
	    return false;
    }

    return true;
}


/**
 * main
 */
int main(int argc, char **argv)
{

    char  *sign_input = "data/msg.txt";

    char *signer_cert = "keys/jiro_cert.pem";
    char *signer_key = "keys/jiro_key.pem";

    char *signer_cacert = "keys/hoge_cacert.pem";


    if(argc == 2) {
      	sign_input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", sign_input);

// no flags
    int sign_flags = 0;
    char *sign_output = "signed_noflags.txt";

    STACK_OF(X509) *verify_certs = NULL;


    bool ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );

    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }



// If the flags PKCS7_STREAM is set then the returned PKCS7 structure is just initialized ready to perform the signing operation
//The data being signed is included in the PKCS7 structure, unless PKCS7_DETACHED is set

   sign_flags = PKCS7_STREAM | PKCS7_DETACHED ;
    sign_output = "signed_stream_detached.txt";

     ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );
    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }

   sign_flags = PKCS7_STREAM;
    sign_output = "signed_stream.txt";

     ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );
    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }


// If PKCS7_NOATTR is set then no authenticatedAttributes will be used. 

    sign_flags = PKCS7_STREAM | PKCS7_NOATTR ;
    sign_output = "signed_stream_noattr.txt";

     ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );
    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }


// If PKCS7_NOSMIMECAP is set then just the SMIMECapabilities are omitted.

    sign_flags = PKCS7_STREAM | PKCS7_NOSMIMECAP ;
    sign_output = "signed_stream_nomimecap.txt";

     ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );    
    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }

//If  PKCS7_NOCERTS is set the signer's certificate will not be included in the PKCS7 structure, the signer's certificate must still be supplied in the signcert parameter though. 

    sign_flags = PKCS7_STREAM |  PKCS7_NOCERTS ;
    sign_output = "signed_stream_nocerts.txt";

    X509 *cert =  new_X509( signer_cert );

   ver_certs = sk_X509_new_null();

    if ( !sk_X509_push(ver_certs, cert ) ) {
       ERR_print_errors_fp(stderr);
    }

     ret = test_sign_verify( sign_input, sign_output, signer_cert, signer_key, sign_flags,  signer_cacert,ver_certs );
    if(!ret){
        printf("test_sign_verify faild: %d %s \n", sign_flags, sign_output );
	    return EXIT_FAILURE;
    }


    printf("test successful \n");
    return EXIT_SUCCESS;

}


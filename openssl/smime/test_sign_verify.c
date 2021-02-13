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


/**
 * main
 */
int main(int argc, char **argv)
{

    char  *input = "data/msg.txt";

    char *sign_output = "signed.txt";
    char *verify_output = "verified.txt";

    char *signer_cert = "keys/jiro_cert.pem";
    char *signer_key = "keys/jiro_key.pem";

    if(argc == 2) {
      	input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", input);

    bool ret1 = smime_sign_stream_detached( input , sign_output, signer_cert, signer_key );

    if(ret1) {
        printf("sign successful \n");
        if ( file_exists(sign_output) ) {
            printf("saved: %s \n", sign_output);
        }
    } else {
        printf("sign faild \n");
	    return EXIT_FAILURE;
    }

    int verify_flags = 0;
    bool ret2 = smime_verify( sign_output , verify_output, signer_cert, verify_flags );

    if(ret2) {
        printf("verify successful \n");
        if ( file_exists(verify_output) ) {
            printf("saved: %s \n", verify_output );
        }
    } else {
        printf("verify faild \n");
	    return EXIT_FAILURE;
    }


    char error[100];

    char *original = file_text_read( input, (char *)error );

    if(!original) {
        printf("file_text_read faild: %s \n", input);
	    return EXIT_FAILURE;
    }

    char *verify = file_text_read( verify_output, (char *)error );

    if(!verify) {
        printf("file_text_read faild: %s \n", verify_output );
	    return EXIT_FAILURE;
    }

    if( strcmp(original, verify) != 0 ) {
        printf("unmatch \n");
	    return EXIT_FAILURE;
    }

    printf("test successful \n");
    return EXIT_SUCCESS;

}


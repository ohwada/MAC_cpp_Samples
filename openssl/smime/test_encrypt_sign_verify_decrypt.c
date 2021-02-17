/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// Simple S/MIME encrypt sign verify decrypt example 
// send mail from Jiro to Taro 


// gcc test_encrypt_sign_verify_decrypt.c  `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include "smime.h"
#include "file_util.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char  *enc_input = "data/msg.txt";

    char *recpt_cert = "keys/taro_cert.pem";
    char *recpt_key = "keys/taro_key.pem";

    char *signer_cert = "keys/jiro_cert.pem";
    char *signer_key = "keys/jiro_key.pem";

   char *signer_cacert = "keys/hoge_cacert.pem";

    if(argc == 2) {
      	enc_input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", enc_input);

    char *enc_output= "encrypted.txt";

    bool ret1 = smime_encrypt_stream( enc_input , encrypt_output, recpt_cert );

    if(ret1) {
        printf("encrypt successful \n");
        if ( file_exists( encrypt_output) ) {
            printf("saved: %s \n",  enc_output);
        }
    } else {
        printf("encrypt faild: %s \n", enc_output);
	    return EXIT_FAILURE;
    }

    char *sign_output = "signed.txt";

    bool ret2 = smime_sign_stream_detached( enc_output, sign_output,  signer_cert,  signer_key );

    if(ret2) {
        printf("sign successful \n");
        if ( file_exists(sign_output) ) {
            printf("saved: %s \n", sign_output);
        }
    } else {
        printf("sign faild \n");
	    return EXIT_FAILURE;
    }

    char *verify_output = "verified.txt";

    bool ret3 = smime_verify_default( sign_output , verify_output, signer_cacert );

    if(ret3) {
        printf("verify successful \n");
        if ( file_exists(verify_output) ) {
            printf("saved: %s \n",ver_output );
        }
    } else {
        printf("verify faild \n");
	    return false;
    }

    char *dec_output= "decrypted.txt";

    bool ret4 = smime_decrypt_default(ver_output , decrypt_output, recpt_cert, recpt_key );

    if(ret4) {
        printf("decrypt successful \n");
        if ( file_exists(decrypt_output) ) {
            printf("saved: %s \n", decrypt_output);
        }
    } else {
        printf("decrypt faild \n");
	    return false;
    }


    char error[100];

    char *original = file_text_read( enc_input, (char *)error );

    if(!original) {
        printf("file_text_read faild: %s \n", enc_input);
	    return false;
    }

    char *decrypt = file_text_read( decrypt_output, (char *)error );

    if(!decrypt) {
        printf("file_text_read faild: %s \n", dec_output);
	    return false;
    }

    if( strcmp(original, decrypt) != 0 ) {
        printf("unmatch \n");
	    return false;
    }


    printf("test successful \n");
    return EXIT_SUCCESS;

}


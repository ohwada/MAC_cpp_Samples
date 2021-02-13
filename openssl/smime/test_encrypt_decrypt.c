/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// Simple S/MIME encrypt decrypt example 
// send mail from Jiro to Taro 


// gcc  test_encrypt_decrypt.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include "smime.h"
#include "file_util.h"


/**
 * main
 */
int main(int argc, char **argv)
{

    char  *input = "data/msg.txt";

    char *encrypt_output = "encrypted.txt";
    char *decrypt_output = "decrypted.txt";

    char *recpt_cert = "keys/taro_cert.pem";
    char *recpt_key = "keys/taro_key.pem";

    if(argc == 2) {
      	input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", input);

    bool ret1 = smime_encrypt_stream( input , encrypt_output, recpt_cert );

    if(ret1) {
        printf("encrypt successful \n");
        if ( file_exists(encrypt_output) ) {
            printf("saved: %s \n", encrypt_output );
        }
    } else {
        printf("encrypt faild \n");
	    return EXIT_FAILURE;
    }

    int decrypt_flags = 0;
    bool ret2 = smime_decrypt( encrypt_output , decrypt_output, recpt_cert, recpt_key, decrypt_flags );

    if(ret2) {
        printf("decrypt successful \n");
        if ( file_exists(decrypt_output) ) {
            printf("saved: %s \n", decrypt_output);
        }
    } else {
        printf("decrypt faild \n");
	    return EXIT_FAILURE;
    }

    char error[100];

    char *original = file_text_read( input, (char *)error );

    if(!original) {
        printf("file_text_read faild: %s \n", input);
	    return EXIT_FAILURE;
    }

    char *decrypt = file_text_read( decrypt_output, (char *)error );

    if(!decrypt) {
        printf("file_text_read faild: %s \n", decrypt_output );
	    return EXIT_FAILURE;
    }

    if( strcmp(original, decrypt) != 0 ) {
        printf("unmatch \n");
	    return EXIT_FAILURE;
    }

    printf("test successful \n");
    return EXIT_SUCCESS;

}


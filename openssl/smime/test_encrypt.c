/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// Simple S/MIME encrypt decrypt example 
// send mail from Jiro to Taro 


// gcc  test_encrypt.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include "smime.h"
#include "file_util.h"

bool test_encrypt( char *input , char *output, char *recpt_cert, int flags )
{

    bool ret = smime_encrypt( input , output, recpt_cert, flags );

    if(ret) {
        printf("encrypt successful \n");
        if ( file_exists(output) ) {
            printf("saved: %s \n", output );
        }
    } else {
        printf("encrypt faild: %d %s \n", flags, output );
	    return false;
    }

    return true;
}

/**
 * main
 */
int main(int argc, char **argv)
{

    char  *input = "data/msg.txt";

    char *recpt_cert = "keys/taro_cert.pem";
    char *recpt_key = "keys/taro_key.pem";

    if(argc == 2) {
      	input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", input);


  // On OpenSSL 0.9.9 only:
  //  for streaming set PKCS7_STREAM
// if the PKCS7_STREAM flag is set 
// a partial PKCS7 structure is output suitable for streaming I/O
    int flags = PKCS7_STREAM;

    char *output = "encrypted_stream.txt";

    bool ret =test_encrypt( input , output, recpt_cert, flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }

// Normally the supplied content is translated into MIME canonical format (as required by the S/MIME specifications)
    flags = 0;

    output = "encrypted_noflags.txt";

    ret = test_encrypt( input , output, recpt_cert, flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }


// If the PKCS7_TEXT flag is set MIME headers for type text/plain are prepended to the data.
    flags = PKCS7_TEXT;

    output = "encrypted_text.txt";

    ret = test_encrypt( input , output, recpt_cert, flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }


//if PKCS7_BINARY is set no translation occurs. This option should be used if the supplied data is in binary format otherwise the translation will corrupt it.     
    flags = PKCS7_BINARY;

    output = "encrypted_binary.txt";

    ret = test_encrypt( input , output, recpt_cert, flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }


    printf("test successful \n");
    return EXIT_SUCCESS;

}


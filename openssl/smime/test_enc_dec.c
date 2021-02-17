/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// Simple S/MIME encrypt decrypt example 
// send mail from Jiro to Taro 


// gcc  test_enc_de.c `pkg-config --cflags --libs openssl` 


#include <stdio.h>
#include <stdlib.h>
#include "smime.h"
#include "file_util.h"

bool test_enc_dec( char *enc_input , char *enc_output, char *recpt_cert,  char *recpt_key, int enc_flags, int dec_flags )
{

    char dec_output[100];
    strcpy(dec_output, "decrypted_");
    strcat(dec_output, enc_output);

   EVP_CIPHER *cipher = 
    (EVP_CIPHER *)EVP_des_ede3_cbc();

    bool ret1 = smime_encrypt( enc_input , enc_output, recpt_cert,  cipher,  enc_flags );

    if(ret1) {
        printf("encrypt successful \n");
        if ( file_exists( enc_output) ) {
            printf("saved: %s \n",  enc_output );
        }
    } else {
        printf("encrypt faild: %d %s \n", enc_flags,  enc_output );
	    return false;
    }

    bool ret2 = smime_decrypt( enc_output , dec_output, recpt_cert, recpt_key, dec_flags );

    if(ret2) {
        printf("decrypt successful \n");
        if ( file_exists(dec_output) ) {
            printf("saved: %s \n", dec_output);
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

    char *decrypt = file_text_read( dec_output, (char *)error );

    if(!decrypt) {
        printf("file_text_read faild: %s \n", dec_output );
	    return false;
    }

    if( strcmp(original, decrypt) != 0 ) {
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

    char  *enc_input = "data/msg.txt";

    char *recpt_cert = "keys/taro_cert.pem";
    char *recpt_key = "keys/taro_key.pem";

    if(argc == 2) {
      	enc_input = argv[1];
    } else {
        printf( "Usage: %s  [input] \n",  argv[0] );
    }

    printf("input: %s \n", enc_input);

// Normally the supplied content is translated into MIME canonical format (as required by the S/MIME specifications)

    int enc_flags = 0;
    int dec_flags = 0;
    char *enc_output = "encrypted_noflags.txt";

    bool ret = test_enc_dec( enc_input , enc_output, recpt_cert,  recpt_key, enc_flags, dec_flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }


  // On OpenSSL 0.9.9 only:
  //  for streaming set PKCS7_STREAM
// if the PKCS7_STREAM flag is set 
// a partial PKCS7 structure is output suitable for streaming I/O

    enc_flags = PKCS7_STREAM;
    enc_output = "encrypted_stream.txt";

    ret =test_enc_dec( enc_input , enc_output, recpt_cert,  recpt_key, enc_flags, dec_flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }


//if PKCS7_BINARY is set no translation occurs. This option should be used if the supplied data is in binary format otherwise the translation will corrupt it.   
  
    enc_flags = PKCS7_BINARY;
    enc_output = "encrypted_binary.txt";

    ret = test_enc_dec( enc_input , enc_output, recpt_cert, recpt_key, enc_flags, dec_flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }

// If the PKCS7_TEXT flag is set MIME headers for type text/plain are prepended to the data.

    enc_flags = PKCS7_TEXT;
    dec_flags = PKCS7_TEXT;
    enc_output = "encrypted_text.txt";

    // in this case decrypt fails
    ret = test_enc_dec( enc_input , enc_output, recpt_cert,  recpt_key, enc_flags, dec_flags );
    if(!ret) {
	    return EXIT_FAILURE;
    }

    printf("test successful \n");
    return EXIT_SUCCESS;

}


// enc_input: data/msg.txt 
// encrypt successful 
// saved: encrypted_noflags.txt 
// decrypt successful 
// saved: decrypted_encrypted_noflags.txt 
// test successful 


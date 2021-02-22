/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// verify localhost cert

// gcc verify_localhost.c  `pkg-config --cflags --libs openssl`

#include <stdio.h>
#include <stdlib.h>
#include "verify_cert.h"


/**
 * main
 */
int main(int argc, char **argv)
{

 char *file_cert = "../certs/localhost_inter_signed_cert.pem";

  char *file_cacert = "../certs/hoge_ca_chain_cert.pem";


    if(argc == 3) {
      	file_cert  = argv[1];
        file_cacert = argv[2];
    } else if(argc == 2) {
      	file_cert  = argv[1];
    } else {
        printf( "Usage: %s  [cert] [cacert] \n",  argv[0] );
    }

  
    printf( "cacert: %s \n",  file_cacert );

    printf( "\n");
    printf( "cert: %s \n",  file_cert );
    bool ret1 = print_subject_name(file_cert);
    printf( "\n");

    if( !ret1) {
        return EXIT_FAILURE;
    }

    bool ret2 = verfy_cert( file_cert, file_cacert,  NULL );

    if( ret2) {
        printf("Verification successfull \n");
    } else {
        printf("Verification faild \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// cert: certs/localhost_cert.pem 
// countryName               = JP
// stateOrProvinceName       = Kanagawa
// organizationName          = hoge company
// organizationalUnitName    = hogesection
// commonName                = localhost
// emailAddress              = hoge@example.com
// Verification successfull 

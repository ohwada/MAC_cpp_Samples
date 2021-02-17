/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// verify www.example.org cert

// gcc verify_example_org.c  `pkg-config --cflags --libs openssl`

#include <stdio.h>
#include <stdlib.h>
#include "verify_cert.h"


/**
 * main
 */
int main(int argc, char **argv)
{

 char *file_cert = "certs/www_example_org.pem";

// Note;
// The certificates in the directory must be in hashed form, 
  char *dir_cacert = "digicert";

    if(argc == 3) {
      	file_cert  = argv[1];
        dir_cacert = argv[2];
    } if(argc == 2) {
      	file_cert  = argv[1];
    } else {
        printf( "Usage: %s  [cert] [dir] \n",  argv[0] );
    }

    printf( "dir: %s \n",  dir_cacert );


    printf( "\n");
    printf( "cert: %s \n",  file_cert );
    bool ret1 = print_subject_name(file_cert);
    printf( "\n");

    if( !ret1) {
        return EXIT_FAILURE;
    }

    bool ret2 = verfy_cert( file_cert, NULL, dir_cacert );

    if( ret2) {
        printf("Verification successfull \n");
    } else {
        printf("Verification faild \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// cert: certs/www_example_org.pem 
// countryName               = US
// stateOrProvinceName       = California
// localityName              = Los Angeles
// organizationName          = Internet Corporation for // Assigned Names and Numbers
//                = www.example.org
// Verification successfull 
/**
 * gnutls sample
 * 2020-07-01 K.OHWADA
 */


// display version

#include <stdio.h>
#include <stdlib.h>
#include <gnutls/gnutls.h>


/**
 * main
 */
int main(void)
{

    printf( "libgnutls version: %s \n", gnutls_check_version(NULL) );

    return EXIT_SUCCESS;
}


// libgnutls version: 3.6.15 


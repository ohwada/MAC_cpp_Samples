/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// display version

#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>


int main(void)
{

    printf( "MHD Version: %s \n", MHD_get_version() );

    return EXIT_SUCCESS;
}


// MHD Version: 0.9.71 




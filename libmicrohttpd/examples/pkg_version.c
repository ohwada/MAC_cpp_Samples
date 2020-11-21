/**
 * libmicrohttpd sample
 * 2020-07-01 K.OHWADA
 */

// display package version

#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>
#include "platform.h"


int main(void)
{

    printf( "Package Version: %s \n", PACKAGE_STRING );

    printf( "MHD Version: %s \n", MHD_get_version() );

    return EXIT_SUCCESS;
}


// Package Version: libmicrohttpd 0.9.19 
// MHD Version: 0.9.71 



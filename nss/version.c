/**
 * nss sample
 * 2021-02-01 K.OHWADA
 */

// display version

// gcc version.c `pkg-config --cflags --libs nss` 


#include <stdio.h>
#include <stdlib.h>
#include <nss.h>

int main(void)
{

    printf( "nss Version: %s \n",  NSS_VERSION  );

    return EXIT_SUCCESS;
}


// nss Version: 3.59 


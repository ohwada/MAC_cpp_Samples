/**
 * C time sample
 * 2020-03-01 K.OHWADA
 */

// display RFC822 / ISO8601 datetime

// gcc datetime.c

#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"


/**
 * main
 */
int main(void)
{

    printf( "%s \n", getDateRfc822() );
    printf( "%s \n", getDateIso8601() );

    return EXIT_SUCCESS;
}


// Sat, 24 Oct 2020 18:02:56 +0900 
// 20201024T180256+0900 


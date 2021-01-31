/**
 * C time sample
 * 2020-03-01 K.OHWADA
 */

// display timesatamp file name

// gcc timestamp.c

#include <stdio.h>
#include <stdlib.h>
#include "timestamp.h"


/**
 * main
 */
int main(void)
{

    const char prefix[] = "file";
    const char ext[] = "txt";

    char filename[100];

    getTimestampFileName( (char *)prefix, (char *)ext,  (char *)filename );

    printf( "%s \n", filename );

    return EXIT_SUCCESS;;
}


// Sat, 24 Oct 2020 18:02:56 +0900 
// 20201024T180256+0900 


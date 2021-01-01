/**
 * system sample
 * 2020-03-01 K.OHWADA
 */

// get home directory
// test for home_directory.h

// gcc test_get_home_directory.c

#include <stdio.h>
#include <stdlib.h>
#include "home_directory.h"


/**
 *  main
 */
int main(void)
{

    printf( "env home: %s \n",  getEnvHome() );

    printf( "pw dir: %s \n",  getPwDir() );

    printf( "home dir: %s \n",  getHomeDir() );

        return EXIT_SUCCESS;
}


// env home: /Users/hoge 
// pw dir: /Users/hoge 
// home dir: /Users/hoge


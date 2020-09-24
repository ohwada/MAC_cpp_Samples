/**
 * C sample
 * 2020-03-01 K.OHWADA
 */

// get home directory

#include <stdio.h>
#include "home_directory.h"


/**
 *  main
 */
int main(void)
{

    printf( "env home: %s \n",  getEnvHome() );

    printf( "pw dir: %s \n",  getPwDir() );

    printf( "home dir: %s \n",  getHomeDir() );

    return 0;
}


// env home: /Users/hoge 
// pw dir: /Users/hoge 
// home dir: /Users/hoge


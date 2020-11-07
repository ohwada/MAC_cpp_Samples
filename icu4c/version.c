/**
 * icu4c sample
 * 2020-07-01 K.OHWADA
 */


// display version

#include <stdio.h>
#include <stdlib.h>
#include <unicode/uversion.h>


/**
 * main
 */
int main(void)
{

    UVersionInfo versionArray;
    u_getVersion(versionArray);


    char *versionString;
    u_versionToString(versionArray, versionString);

    printf( "icu version: %s \n", versionString );

    return EXIT_SUCCESS;
}


// icu version: 67.1 


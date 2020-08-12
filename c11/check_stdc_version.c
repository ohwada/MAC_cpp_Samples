/**
 * C sample
 * 2020-03-01 K.OHWADA
 */


// check STDC_VERSION
// reference : https://programming-place.net/ppp/contents/c/appendix/reference/__STDC_VERSION__.html

#include<stdio.h>
#include<stdlib.h>


/**
 *  main
 */
int main(void)
{
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ == 201112L
        puts( "Compliant with C11" );
    #elif __STDC_VERSION__ == 199901L
        puts( "Compliant with C99" );
    #elif __STDC_VERSION__ == 199409L
        puts( "Compliant with C95" );
    #else
        printf( "STDC_VERSION: %ld /n", __STDC_VERSION__ );
    #endif
#else
    puts( "STDC_VERSION:  not defined" );
#endif

    return EXIT_SUCCESS;
}

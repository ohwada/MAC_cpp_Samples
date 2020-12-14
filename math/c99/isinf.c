/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// isinf: 
// determines if the given floating point number arg is positive or negative infinity.

// https://en.cppreference.com/w/c/numeric/math/isinf

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{
    double a = 1.0;
    double b = 0.0;
    double c = a / b;
    int d = isinf(c);

    printf("isinf:  %.1f / %0.1f ; %d \n", a, b, d );

    double x = 800;
    double y = exp(x);
    int z = isinf(y);

    printf("isinf: exp(%.1f) ;  %d \n", x, z );

    return EXIT_SUCCESS;
}


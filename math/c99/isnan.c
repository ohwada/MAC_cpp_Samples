/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// isnan: 
// determines if the given floating point number arg is a not-a-number (NaN) value

// https://en.cppreference.com/w/c/numeric/math/isnan

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{
    double a = 0.0;
    double b = 0.0;
    double c = a / b;
    int d = isnan(c);

    printf("isnan:  %.1f / %0.1f ; %d \n", a, b, d );

    double x = -1.0;
    double y = sqrt(x);
    int z = isnan(y);

    printf("isnan: sqrt(%.1f) ;  %d \n", x, z );

    return EXIT_SUCCESS;
}


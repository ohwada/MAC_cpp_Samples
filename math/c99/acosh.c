/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// acosh: 
// computes the inverse hyperbolic cosine

// https://en.cppreference.com/w/c/numeric/math/acosh

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{

for(int i=0; i<11; i++)
{
    double x = (double)i / 10;
    double y = cosh(x);
    double z = acosh(y);
    printf("x: %0.1f ; cosh: %.3f ; acosh: %.3f\n", x, y, z);
}

    return EXIT_SUCCESS;
}


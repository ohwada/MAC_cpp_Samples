/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// sinhl: 
// computes hyperbolic sine

// https://en.cppreference.com/w/c/numeric/math/sinh

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
    long double x = (long double)i / 10;
    long double y = sinhl(x);
    printf("x: %0.1Lf ; sinhl: %.3Lf \n", x, y);
}

    return EXIT_SUCCESS;
}


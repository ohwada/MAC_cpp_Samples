/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// double hypot( double x, double y ): 
// computes the square root of the sum of the squares of x and y

// https://en.cppreference.com/w/c/numeric/math/hypot
// https://en.wikipedia.org/wiki/Hypot

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{

for(int i=1; i<10; i++)
{
    double x = (double)i;
    double y = x + 1.0;
    double z = hypot(x, y);
    printf(" hypot( %.1f, %.1f) : %.3f \n", x, y, z);
}

    return EXIT_SUCCESS;
}


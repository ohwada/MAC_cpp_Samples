/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// expm1: 
// computes the e (Euler's number, 2.7182818) raised to the given power arg, minus 1.0 

// https://en.cppreference.com/w/c/numeric/math/expm1


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
    double x = (double)i;
    double y = expm1(x);
    printf(" expm1( %.1f) : %.3f \n", x, y);
}

    return EXIT_SUCCESS;
}


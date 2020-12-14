/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// lround: 
// computes the nearest integer value to arg (in floating-point format)

// https://en.cppreference.com/w/c/numeric/math/round

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{

for(int i=21; i<31; i++)
{
    double x = (double)i / 10;
    long y = lround(x);
    printf(" lround( %.2f) : %ld \n", x, y);
}

    return EXIT_SUCCESS;
}


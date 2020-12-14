/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// erf: 
// computes the error function 

// https://en.cppreference.com/w/c/numeric/math/erf
// https://en.wikipedia.org/wiki/Error_function

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
    double y = erf(x);
    printf(" erf( %.1f) : %.3f \n", x, y);
}

    return EXIT_SUCCESS;
}


/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// tgamma: 
// computes the gamma function of arg.

// https://en.cppreference.com/w/c/numeric/math/tgamma
// https://en.wikipedia.org/wiki/Gamma_function

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
    double y = tgamma(x);
    printf(" tgamma( %.1f) : %.3f \n", x, y);
}

    return EXIT_SUCCESS;
}


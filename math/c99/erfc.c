/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// erfc: 
// computes the complementary error function of arg, 
// that is 1.0-erf(arg)

// https://en.cppreference.com/w/c/numeric/math/erfc
// https://en.wikipedia.org/wiki/Error_function#Complementary_error_function

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
    double y = erfc(x);
    printf(" erfc( %.1f) : %.3f \n", x, y);
}

    return EXIT_SUCCESS;
}


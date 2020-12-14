/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// atanh: 
// computes the inverse hyperbolic tangent

// https://en.cppreference.com/w/c/numeric/math/atanh

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
    double y = tanh(x);
    double z = atanh(y);
    printf("x: %0.1f ; tanh: %.3f ; atanh: %.3f\n", x, y, z);
}

    return EXIT_SUCCESS;
}


/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// fmax: 
//  returns the larger of two floating point arguments, 

// https://en.cppreference.com/w/c/numeric/math/fmax

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
    double a = (double)i / 10;
    double b = a + 0.01;
    double c = fmax(a, b);
    printf(" fmax( %.3f, %.3f) : %.3f \n", a, b, c);
}

    return EXIT_SUCCESS;
}


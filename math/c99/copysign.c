/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// double copysign( double x, double y );		
// omposes a floating point value with the magnitude of x and the sign of y.

https://en.cppreference.com/w/c/numeric/math/copysign

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{

for(int i=1; i<11; i++)
{
    double x = (double)i;
    double y = -1;
    double z = copysign(x, y);
    printf(" copysign( %.1f, %.1f) : %.1f \n", x, y, z);
}

    return EXIT_SUCCESS;
}


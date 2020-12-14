/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// isgreater(x, y): 
// determines if the floating point number x is greater than the floating-point number (y)

// https://en.cppreference.com/w/c/numeric/math/isgreater

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
    double y = x - 0.1;
    int z = isgreater(x, y);
    printf(" isgreater( %.2f, %.2f) : %d \n", x, y, z);
}

    return EXIT_SUCCESS;
}


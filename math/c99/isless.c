/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// isless(x, y): 
// determines if the floating point number x is less than the floating-point number y

// https://en.cppreference.com/w/c/numeric/math/isless

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
    double y = x + 0.1;
    int z = isless(x, y);
    printf(" isless( %.2f, %.2f) : %d \n", x, y, z);
}

    return EXIT_SUCCESS;
}


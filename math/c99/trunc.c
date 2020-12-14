/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// trunc: 
// computes the nearest integer not greater in magnitude than arg

// https://en.cppreference.com/w/c/numeric/math/trunc

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
     double y = trunc(x);
    printf(" trunc( %.2f) : %.1f \n", x, y);
}

    return EXIT_SUCCESS;
}


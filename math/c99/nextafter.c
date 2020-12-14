/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// double nextafter( double from, double to ): 
// returns the next representable value of from in the direction of to

// https://en.cppreference.com/w/c/numeric/math/nextafter
// https://stackoverflow.com/questions/12063821/nextafter-vs-nexttoward-functions-in-c-2011

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
    double from = (double)i;
    double to = from + 1;
    double y = nextafter(from, to);
    printf(" nextafter( %.1f, %.1f) : %.16f \n", from, to, y);
}

    return EXIT_SUCCESS;
}


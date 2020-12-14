/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// isunordered: 
// determines if the floating point numbers x and y are unordered, 

// https://en.cppreference.com/w/c/numeric/math/isunordered

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{
    double a = 0.0;
    double b = 1.0;
    int c = isunordered(a, b);

    printf("isunordered( %.1f, %0.1f ): %d \n", a, b, c );

    double x = 0.0;
    double y = nan(NULL);
    int z = isunordered(x, y);

   printf("isunordered( %.1f, %0.1f ): %d \n", x, y, z );


    return EXIT_SUCCESS;
}


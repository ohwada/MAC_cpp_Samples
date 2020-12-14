/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// asinh: 
// The area hyperbolic sine 
// computes  the inverse operation of the hyperbolic sine (sinh)

// http://www.cplusplus.com/reference/cmath/asinh/

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
    double y = sinh(x);
    double z = asinh(y);
    printf("x: %0.1f ; sinh: %.3f ; asinh: %.3f\n", x, y, z);
}

    return EXIT_SUCCESS;
}


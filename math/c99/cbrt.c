/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// cbrt:
// computes the cubic root

// https://en.cppreference.com/w/c/numeric/math/cbrt


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* main */
int main(void) 
{

for(int i=1; i<10; i++)
{

    int x = i * i * i;

    double y = cbrt(( double)x );

    printf("%d : 3rd power:%d ; cube root: %.1f \n", i, x, y);
}

    return EXIT_SUCCESS;
}


// 1 : 3rd power:1 ; cube root: 1.0 
// 2 : 3rd power:8 ; cube root: 2.0 
// 3 : 3rd power:27 ; cube root: 3.0 


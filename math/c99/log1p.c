/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// log1p: 
//  computes the natural (base e) logarithm of 1+arg. log(1+arg)

// https://en.cppreference.com/w/c/numeric/math/log1p
// https://stackoverflow.com/questions/49538185/what-is-the-purpose-of-numpy-log1p/56213786

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
    double y = log1p(x);
    printf(" log1p( %.3f) : %.3f \n", x, y);
}

    return EXIT_SUCCESS;
}


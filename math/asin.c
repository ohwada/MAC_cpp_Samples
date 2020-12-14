/**
 * math sample
 * 2020-07-01 K.OHWADA
 */

// asin:
// returns the arc sine (inverse sine)

// https://www.programiz.com/c-programming/library-function/math.h/asin


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
 * main 
*/
int main(void) 
{

double deg_to_rad =  M_PI / 180;

for(int i=0; i <= 95; i += 5)
{
    double rad =  i * deg_to_rad ;
    double y = sin(rad);
    double r_rad = asin(y);
    double r_deg = r_rad / deg_to_rad;
    printf("%d : sin: %.3f ; asin: %.1f \n", i, y, r_deg );
}

    return EXIT_SUCCESS;
}


// 0 : sin: 0.000 ; asin: 0.0 
// 5 : sin: 0.087 ; asin: 5.0 




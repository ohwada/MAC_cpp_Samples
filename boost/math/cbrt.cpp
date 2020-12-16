/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// computes the cubic root
// reference : https://www.boost.org/doc/libs/1_39_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/extern_c/tr1.html


#include <iostream>
#include <boost/math/tr1.hpp>



using namespace std;


/**
 * main
 */
int main(void) 
{

for(int i=1; i<10; i++)
{

    int x = i * i * i;

    double y = boost::math::tr1::cbrt( ( double)x );

    printf("%d : 3rd power:%d ; cube root: %.1f \n", i, x, y);
}

    return EXIT_SUCCESS;
}
'
// 1 : 3rd power:1 ; cube root: 1.0 
// 2 : 3rd power:8 ; cube root: 2.0 
// 3 : 3rd power:27 ; cube root: 3.0 


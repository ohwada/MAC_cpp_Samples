/**
 *  constexpr.cpp 
 * 2022-06-01 K.OHWADA
 */

// g++ constexpr14.cpp =std=c++14

// reference : https://cpplover.blogspot.com/2014/10/c14-constexpr.html

#include <iostream>


/**
 * sqrt
 */
template < typename T >
constexpr T sqrt( T s )
{
    T x = s / 2.0 ;
    T prev = 0.0 ;

    while ( x != prev )
    {
        prev = x ;
        x = (x + s / x ) / 2.0 ;
    }
    return x ;
}


/**
 *  main
 */
int main()
{
    double x = 2.0;

	std::cout << sqrt(x) << std::endl;

	return 0;
}

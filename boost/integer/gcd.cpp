/**
 * gcd.cpp
* Greatest Common Divisor
 * 2022-06-01 K.OHWADA
 */

// g++ gcd.cpp -std=c++11
// reference : http://www.kmonos.net/alang/boost/classes/common_factor.html

#include <iostream>
#include  <boost/integer/common_factor_rt.hpp>


using namespace std;


/**
 * main
 */
int main()
{
	int a=6;
	int b = 15;

// Greatest Common Divisor
	cout 
	     << "gcd(" << a << "," << b << ")="<< boost::integer::gcd(a, b)  << endl;

// Least Common Multiple
	cout 
	     << "lcm(" << a << "," << b << ")="<< boost::integer::lcm(a, b)  << endl;

	return 0;
}

// gcd(6,15)=3
// lcm(6,15)=30


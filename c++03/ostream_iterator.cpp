/**
 *  ostream_iterator.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  ostream_iterator.cpp
// reference ; https://cpprefjp.github.io/reference/iterator/ostream_iterator.html

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>


/**
 *  main
 */
int main()
{
 	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

// output to std::cout while iterating the elements of v
// (comma as delimiter)
  	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;

	return 0;

}

// 1,2,3,


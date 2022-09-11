/**
 *  lambda.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ lambda.cpp -std=c++14

// https://gintenlabo.hatenablog.com/entry/20130516/1368711542

#include <iostream>


/**
 *  main
 */
int main()
{

auto plus_one = [] (auto x) {
  return x + 1;
};

int x= 0;
double y = 1.5;

std::cout << plus_one(x) << std::endl;
std::cout << plus_one(y) << std::endl;


	return 0;
}


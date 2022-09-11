/**
 *   integer_sequence.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ integer_sequence.cpp -std=c++14
// reference : https://cpprefjp.github.io/reference/utility/integer_sequence.html
#include <iostream>
#include <utility>


/**
 *   g
 */
void g(int a, int b, int c)
{
  std::cout << a << ", " << b << ", " << c << std::endl;
}


/**
 *  f
 */
template <class T, T... Seq>
void f(std::integer_sequence<T, Seq...>)
{
// Take the constant sequence {0, 1, 2} and forward it as an argument to the function g()
  g(Seq...);
}


/**
 *   main
 */
int main()
{
  f(std::integer_sequence<int, 0, 1, 2>());
	return 0;
}


// 0, 1, 2


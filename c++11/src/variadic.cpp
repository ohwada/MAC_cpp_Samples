 /**
 *  variadic.cpp
 * variadic_templates
 * 2022-06-01 K.OHWADA
 */

//  g++ variadic.cpp

// reference : https://cpprefjp.github.io/lang/cpp11/variadic_templates.html

#include <iostream>
#include <utility>


 /**
 *  print
 * exit when the parameter pack is empty
 */
void print() {}


 /**
 *  print
 * receive one or more parameters
 * split the variadic argument into the beginning and the rest
 */
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
  	std::cout << head << std::endl;

// divide the parameter pack tail into head and tail
  	print(std::forward<Tail>(tail)...);
}


 /**
 *  main
 */
int main()
{
  print(1, 'a', "hello");
}


// 1
// a
// hello




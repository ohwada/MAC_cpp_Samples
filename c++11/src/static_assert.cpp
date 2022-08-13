/**
 *  static_assert.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  static_assert.cpp -std=c++11

// reference : https://cpprefjp.github.io/lang/cpp11/static_assert.html 

#include <type_traits>


/**
 *  struct X
 */
template <class T>
struct X {
  static_assert(std::is_integral<T>::value, "template parameter T must be integral type");

  // …
};


/**
 *  main
 */
int main()
{
  X<int>(); // OK
//X<double>(); // compile error : template parameter T must be integral type
}



/**
 *  swap.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  swap.cpp -std=c++11
// reference : https://cpprefjp.github.io/reference/vector/vector/swap.html
#include <iostream>
#include <vector>


/**
 *  print
 */
template <class T>
void print(const char* name, const std::vector<T>& v)
{
  std::cout << name << " : {";

  for (const T& x : v) {
    std::cout << x << " ";
  }

  std::cout << "}" << std::endl;
}


/**
 *  main
 */
int main()
{
  std::vector<int> v1 = {1, 2, 3};
  std::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  print("v1", v1);
  print("v2", v2);

	return 0;
}

// v1 : {4 5 6 }
// v2 : {1 2 3 }


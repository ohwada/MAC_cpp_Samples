/**
 *  make_shared.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ make_shared.cpp -std=c++11
// reference :  https://cpprefjp.github.io/reference/memory/make_shared.html

#include <memory>
#include <iostream>


/**
 *  main
 */
int main() 
{
  std::shared_ptr<int> sp = std::make_shared<int>(42);
  if(sp) {
    std::cout << *sp << std::endl;
  }
	return 0;
}

// 42


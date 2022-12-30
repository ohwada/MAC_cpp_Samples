/**
 *   unique_ptr.cpp
 * 2022-06-01 K.OHWADA
 */

// https://cpprefjp.github.io/reference/memory/unique_ptr.html

#include <cstdlib>
#include <memory>
#include <iostream>


/**
 * struct hoge
 */
struct hoge {
  hoge() { std::cout << "hoge::hoge()" << std::endl; }
  ~hoge() { std::cout << "hoge::~hoge()" << std::endl; }
};

using  namespace std;


/**
 * main
 */
int main() 
{
  std::unique_ptr<hoge> p0(new hoge());

// Move ownership of hoge object from p0 to p1
// p0 now owns nothing
  std::unique_ptr<hoge> p1(std::move(p0));

  if (p0) {
// p0 is empty
    std::abort();
  }

// Resources owned by p1 are released
}


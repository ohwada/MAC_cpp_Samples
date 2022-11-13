/**
 * user_defined_literals.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://cpprefjp.github.io/lang/cpp11/user_defined_literals.html

#include <iostream>
#include <string>


/**
 * definition
 */
namespace my_namespace {
inline namespace literals {
  std::string operator"" _s(const char* str, std::size_t length)
  {
    return std::string(str, length);
  }
}}


/**
 * main
 */
int main()
{
  using namespace my_namespace::literals;

  auto x = "hello"_s; // x is of type std::string
  std::cout << x << std::endl;
}


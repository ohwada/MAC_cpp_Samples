/**
 *  chrono_literals.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ chrono_literals.cpp -std=c++14
// https://cpprefjp.github.io/reference/chrono/duration/op_h.html

#include <iostream>
#include <chrono>


/**
 *  main
 */
int main()
{
  using namespace std::literals::chrono_literals;


//3 hours of integer type
  auto hours_i = 3h;

 // 3.1 hours for floating point types
  auto hours_f = 3.1h;

  std::cout << hours_i.count() << std::endl;
  std::cout << hours_f.count() << std::endl;

    return 0;
}

// 3
// 3.1


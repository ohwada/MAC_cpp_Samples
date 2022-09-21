/**
 *  pointer.cpp
 * 2022-06-01 K.OHWADA
 */


// function pointer
// https://qiita.com/kurun_pan/items/f2edd3b834dcaeaa8b2f

#include <iostream>
#include <memory>


/**
 *  class Calc
 */
class Calc {
 public:
  Calc() = default;
  ~Calc() = default;

  void setMethod(int (*method)(int a, int b)) {
    method_ = method;
  }

  int invokeMethod(int a, int b) {
    if (method_)
      return method_(a, b);
    return -1;
  }

 private:
  int (*method_)(int a, int b);
};


/**
 *  add
 */
int add(int a, int b) {
  return a + b;
}


/**
 *  main
 */
int main() 
{
  auto calc = std::make_unique<Calc>();

  calc->setMethod(add);
  std::cout << calc->invokeMethod(1, 2) << std::endl;

  return 0;
}


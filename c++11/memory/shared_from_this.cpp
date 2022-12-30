/**
 *  shared_from_this.cpp
 * 2022-06-01 K.OHWADA
 */

// https://cpprefjp.github.io/reference/memory/enable_shared_from_this/shared_from_this.html

#include <iostream>
#include <cassert>
#include <memory>


/**
 * struct X
 */
struct X : public std::enable_shared_from_this<X> {
  std::shared_ptr<X> f()
  {
// create a shared_ptr object pointing to this
    return shared_from_this();
  }
};


using  namespace std;


/**
 * main
 */
int main()
{
  std::shared_ptr<X> p(new X());
  std::shared_ptr<X> q = p->f();

  assert(p == q);

    cout << "successful" << endl;

    return 0;
}

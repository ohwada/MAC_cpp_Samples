/**
 *  weak_ptr.cpp
 * 2022-06-01 K.OHWADA
 */

// https://cpprefjp.github.io/reference/memory/weak_ptr.html

#include <memory>
#include <iostream>

using  namespace std;


/**
 *  main
 */
int main()
{
// weak_ptr object wp is
  // monitor the shared_ptr object sp
  std::shared_ptr<int> sp(new int(42));
  std::weak_ptr<int> wp = sp;

  
// Process if the sp monitored by wp holds a valid resource.
  if (std::shared_ptr<int> r = wp.lock()) {
    cout << "get weak_ptr value : " << *r << endl;
  }

  sp.reset();

// Detect when the shared_ptr object is no longer valid
  if (wp.expired()) {
    cout << "shared_ptr managed object deleted." << endl;
  }
}

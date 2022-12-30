/**
 *  shared_ptr.cpp
 * 2022-06-01 K.OHWADA
 */


// https://cpprefjp.github.io/reference/memory/shared_ptr.html

#include <iostream>
#include <memory>

using  namespace std;


/**
 *  main
 */
int main()
{
// Let the shared_ptr object manage the new pointer
  // Only one owner.
  std::shared_ptr<int> p1(new int(3));

  cout << "p1: "<< *p1 << endl;

 cout << "p1 use_count: " << p1.use_count() << endl;


  {
// by copying the shared_ptr object,
    // Multiple objects can share a single resource.

    cout << "p2 = p1" << endl;

    std::shared_ptr<int> p2 = p1;

 cout << "p1 use_count: " << p1.use_count() << endl;

// access shared resources
    cout << "p2: " << *p2 << endl;
  }

 // p2's destructor is executed.
    // The resource will have one owner.
    // Resources are not freed here yet.


  cout << "p1: "<< *p1 << endl;
}

// p1's destructor is executed.
  // The resource owner becomes 0.
  // Resources are freed because no one is referencing them anymore.



// p1: 3
// p1 use_count: 1
// p2 = p1
// p1 use_count: 2
// p2: 3
// p1: 3

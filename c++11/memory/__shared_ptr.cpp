/**
 *  shared_ptr.cpp
 * 2022-06-01 K.OHWADA
 */


// https://cpprefjp.github.io/reference/memory/shared_ptr.html

#include <iostream>
#include <memory>


/**
 *  main
 */
int main()
{
// Let the shared_ptr object manage the new pointer
  // Only one owner.
  std::shared_ptr<int> p1(new int(3));

    std::cout << "p1: " << *p1 << std::endl;

    std::cout << "p1 use_count: " << p1.use_count() << endl;
  
{
// by copying the shared_ptr object,
    // Multiple objects can share a single resource.
    // have 2 owners.
    std::shared_ptr<int> p2 = p1;

// access shared resources
    std::cout << "p2: " << *p2 << std::endl;

td::cout << "p2 use_count: " << p2.use_count() << endl;

  {

  } 

// p2's destructor is executed.
    // The resource will have one owner.
    // Resources are not freed here yet.


    std::cout << "p1: " << *p1 << std::endl;

    std::cout << "p1 use_count: " << p1.use_count() << endl;

}
// p1's destructor is executed.
  // The resource owner becomes 0.
  // Resources are freed because no one is referencing them anymore.

 
// p1: 3
// p2: 3
// p1: 3


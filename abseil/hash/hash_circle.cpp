/**
 * asbseil sample
 * 2020-07-01 K.OHWADA
 */


// generate a hash value for the class
// use class as key in hash map
// reference : https://abseil.io/docs/cpp/guides/hash

#include <iostream>
#include <unordered_map>
 #include "absl/hash/hash.h"


using namespace std;


/**
 *  class Circle
 */
class Circle {
 public:
int mc; // center
int mr; // radius

Circle()
{
}

Circle(int _center, int _radius)
{
    mc  = _center;
    mr = _radius;
}

string toString(void)
{
    string str = "[ " + to_string(mc) + ", "
    + to_string(mr) + " ]";
    return str;
}

  template <typename H>
  friend H AbslHashValue(H h, const Circle& c) {
    return H::combine(std::move(h), c.mc , c.mr );
  }

 private:
};

bool operator==(const Circle& c1, const Circle& c2) 
{
  return
    ( ( c1.mc == c2.mc ) &&
    ( c1.mr == c2.mr ) ) ;
}

// ----------


/**
 *  main
 */
int main(void)
{

// std::unordered_map<Circle, Circle> map;
std::unordered_map<Circle, Circle, absl::Hash<Circle>> map;

    Circle c1(1, 2);
    Circle c2(2, 3);
    Circle c3(3, 4);

    Circle c11(11, 2);
    Circle c22(22, 3);
    Circle c33(33, 4);

 map[ c1 ] = c11;
  map[ c2 ] = c22;
  map[ c3 ] = c33;

  for (auto&x : map) {
        auto first = x.first;
        auto second = x.second;
        std::cout << first.toString() << " => "
        << second.toString() << std::endl;
  }

        return 0;
}

// [ 3, 4 ] => [ 33, 4 ]
// [ 2, 3 ] => [ 22, 3 ]
// [ 1, 2 ] => [ 11, 2 ]

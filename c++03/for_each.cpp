/**
 *  for_each.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ for_each.cpp
// reference : https://cpprefjp.github.io/reference/algorithm/for_each.html

#include <iostream>
#include <vector>
#include <algorithm>


/**
 *  disp
 */
void disp(int x) {
  std::cout << x << std::endl;
}


/**
 *  struct mutate
 */
struct mutate {
  int n;
  mutate() : n(0) { }
  void operator()(int& v) {
    v += n++;
  }
};


/**
 *  main
 */
int main() 
{
  std::vector<int> v;

  v.push_back(3);
  v.push_back(1);
  v.push_back(4);


// apply the disp() function to all elements of v
  std::for_each(v.begin(), v.end(), disp);

  std::cout << "----" << std::endl;


// It's okay to rewrite the contents of the element
// It is okay to write processing that depends on the calling order
  std::for_each(v.begin(), v.end(), mutate());
  std::for_each(v.begin(), v.end(), disp);

    return 0;
}

// 3
// 1
// 4
// ----
// 3
// 2
// 6

/**
 *  copy.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ copy.cpp
// reference : https://cpprefjp.github.io/reference/algorithm/copy.html

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>


/**
 *  main
 */
int main() 
{
    std::vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);

// normal copy from v to v2
// make sure enough space
  std::vector<int> v2(v.size());
  std::copy(v.begin(), v.end(), v2.begin());


// set to v3 using back_inserter.
// back_inserter is a function that creates an iterator that v3.push_back() when copying elements.
  std::list<int> ls3;
  std::copy(v2.begin(), v2.end(), std::back_inserter(ls3));


// output using ostream_iterator.
  // ostream_iterator<int>(cout, ",") is an iterator that 
// does cout << x << "," when copying elements.
    std::copy(ls3.begin(), ls3.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    return 0;
}

// 3,1,2,


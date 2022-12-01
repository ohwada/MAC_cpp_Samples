// find_backward.cpp
// https://www.boost.org/doc/libs/1_70_0/libs/algorithm/doc/html/the_boost_algorithm_library/Misc/find_backward.html

#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/algorithm/find_backward.hpp>

using namespace std;

int main()
{
std::vector<int>v = { 3, 1, 2 };

cout << "v: ";
for(auto x: v){
    cout << x << ", ";
}
cout << endl;

cout << "find 1" << endl;
 auto result1 = std::find(v.begin(), v.end(), 1);
  if (result1 == v.end()) {
    cout << "not found" << endl;
  } else {
    cout << "found: " << *result1 << endl;
  }

cout << "find backwowd  1" << endl;
auto result2 = boost::algorithm::find_backward(v.begin(),v.end(), 1 );

  if (result2 == v.end()) {
    std::cout << "not found" << std::endl;
  } else {
    std::cout << "found: " << *result2 << std::endl;
  }

    return 0;
}


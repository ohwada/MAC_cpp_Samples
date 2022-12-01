/**
 * minmax.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.boost.org/doc/libs/1_63_0/libs/algorithm/minmax/index.html#example

#include <iostream>
#include <list>
#include <utility>
#include <cassert>
#include <boost/algorithm/minmax.hpp>

  using namespace std;


/**
 * main
 */
int main()
{

  boost::tuple<int const&, int const&> result1 = boost::minmax(1, 0);

  assert( result1.get<0>() == 0 );
  assert( result1.get<1>() == 1 );

  list<int> L;
  generate_n(front_inserter(L), 1000, rand);

  typedef list<int>::const_iterator iterator;
  pair< iterator, iterator > result2 = minmax_element(L.begin(), L.end());
  cout << "The smallest element is " << *(result2.first) << endl;
  cout << "The largest element is  " << *(result2.second) << endl;

  assert( result2.first  == std::min_element(L.begin(), L.end() ));
  assert( result2.second == std::max_element(L.begin(), L.end() ));

    cout<< "successful" << endl;

    return 0;
}

// The smallest element is 16807
// The largest element is  2146319451


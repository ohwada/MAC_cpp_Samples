/**
 * copy.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/rinse_/items/f00bb2a78d14c3c2f9fa

#include <iostream>
#include <iterator>
#include <vector>
#include <boost/range/algorithm/copy.hpp>

using namespace std;


/**
 * main
 */
int main()
{
    vector<int> vec { 1, 2, 3,4, 5 };

    boost::copy(vec, std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;

    return 0;
}

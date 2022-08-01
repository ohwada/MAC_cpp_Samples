/**
 * optional.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ optional.cpp
// reference : https://boostjp.github.io/tips/optional.html

#include <iostream>
#include <vector>
#include <boost/assign/list_of.hpp>


/**
 *  find_value
 */
int* find_value(std::vector<int>& v, int value)
{
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (v[i] == value)
            return &v[i];
    }
    return NULL;
}


/**
 * main
 */
int main()
{
    std::vector<int> v = boost::assign::list_of(1)(2)(3);

    int* p = find_value(v, 3);
    if (p) {
        std::cout << *p << std::endl;
    } else {
        std::cout << "not applicable" << std::endl;
    }
    return 0;
}

// 3

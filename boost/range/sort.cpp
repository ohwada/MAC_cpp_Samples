/**
 * sort.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://boostjp.github.io/document/boost-range-algorithm-kansu-no-susume.html

#include <vector>
#include <iostream>
#include <boost/range/algorithm.hpp>


/**
 * dump_vec
 */
void dump_vec( std::string name, std::vector<int> vec)
{
    std::cout << name << ": ";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;
}


using namespace std;



/**
 * main
 */
int main()
{
    vector<int> vec;
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);

    dump_vec("vec", vec);

    boost::sort(vec);

   dump_vec("sort", vec);

    return 0;
}

// vec: 3, 2, 1, 
// sort: 1, 2, 3, 


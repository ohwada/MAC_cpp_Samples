// sub_range.cpp
// Boost.Range.Utilities
// https://qiita.com/rinse_/items/f00bb2a78d14c3c2f9fa

#include <iostream>
#include <vector>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>


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


/**
 * dump_sub
 */
void dump_sub( std::string name,   boost::sub_range<std::vector<int>> sub)
{
    std::cout << name << ": ";
    for (std::size_t i = 0; i < sub.size(); ++i) {
        std::cout << sub[i] << ", ";
    }
    std::cout << std::endl;
}


int main()
{
  std::vector<int> vec { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

 dump_vec("vec", vec);


// from beginning to end of vec
  boost::sub_range<std::vector<int>> sub1(vec);
 dump_sub("sub1", sub1);

// represent the 2nd through 9th of vec
  boost::sub_range<std::vector<int>> sub2(begin(vec)+1, begin(vec)+9);
 dump_sub("sub2", sub2);

    return 0;
}


// vec: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
// sub1: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
// sub2: 2, 3, 4, 5, 6, 7, 8, 9,

/**
 * two_int_array.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ two_int_array.cpp -std=c++11 

#include <iostream>
#include <string>
#include <vector>


/**
 * dump
 */
void dump( std::vector<std::vector<int>> vec) 
{
    for (auto rows: vec) {
        std::cout << "{";
        for (auto row: rows) {
            std::cout << row  << ", ";     
        } // for rows
        std::cout << "}" << std::endl;
    } // for vec
}


/**
 * main
 */
int main(void) 
{
  std::vector<std::vector<int>> vec{
    { 32, 4, 78, 34, 64 },
    { 74, 5, 66, 36, 42 },
    { 56, 13, 55, 3, 81 },
    { 7, 56, 33, 83, 4 },
    { 32, 85, 50, 24, 39 },
    { 16, 24, 56, 43, 6 },
    { 75, 35, 27, 34, 83 },
    { 69, 41, 62, 2, 88 }
  };

dump(vec);

  return 0;
}


// {32, 4, 78, 34, 64, }
// {74, 5, 66, 36, 42, }




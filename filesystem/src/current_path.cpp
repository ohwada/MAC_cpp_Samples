/**
 *  current_path.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ current_path.cpp -o bin/current_path  -std=c++17 

// reference : https://cpprefjp.github.io/reference/filesystem/current_path.html

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


/**
 *  main
 */
int main()
{
// get the current working directory
  fs::path p = fs::current_path();
  std::cout << p << std::endl;

// set current working directory
  fs::current_path("/");
  std::cout << fs::current_path() << std::endl;

    return 0;
}

// "/Users/taro/Documents/filesystem/src"

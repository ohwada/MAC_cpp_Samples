/**
 *    show_temp_directory_path.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ fs_temp_directory_path.cpp -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/temp_directory_path.html

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 *   main
 */
int main()
{
  fs::path p = fs::temp_directory_path();
  std::cout << p << std::endl;

	return 0;
}

//  "/var/folders/rj/fn6kfdd924sgfq4d8gvn0qg40000gn/T/"


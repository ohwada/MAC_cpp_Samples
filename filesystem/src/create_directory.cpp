/**
 *  create_directory.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  create_directory.cpp -o  bin/create_dir -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/create_directory.html


#include <iostream>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;


/**
 *  main
 */
int main()
{
 
 string path("new_dir");

  bool result = fs::create_directory(path);

  assert(result);
  assert(fs::exists(path));
  assert(fs::is_directory(path));

// If you specify a directory that already exists, 
// false is returned but no error occurs
  bool result2 = fs::create_directory(path);
  assert(!result2);

    cout << "creted: " << path << endl;

    return 0;
}


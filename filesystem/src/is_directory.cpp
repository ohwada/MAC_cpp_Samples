/**
 *  is_directory.cpp
 * 2022-06-01 K.OHWADA
 */

// ln -s sample2 dir_symlink
// g++ is_directory.cpp -o bin/is_dir -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/is_directory.html

#include <iostream>
#include <string>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;

/**
 *  main
 */
int main()
{
    string path("sample2");
    string file("regular.txt");
    string symlink("dir_symlink");


  // (1)
// use the obtained file status to check if it is a directory
  assert(fs::is_directory(fs::status(path)));


  // (2)
// specify a path and check if it's a directory.
  // symbolic links are determined by the destination file
  assert(fs::is_directory(path));
  assert(fs::is_directory(symlink));
  assert(!fs::is_directory(file));


  // (3)
  // receive error information in error_code instead of exception
  std::error_code ec;
  bool result = fs::is_directory(path, ec);
  assert(!ec);
  assert(result);

    cout << "successful" << endl;

    return 0;
}


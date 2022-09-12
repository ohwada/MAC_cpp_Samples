/**
 *  is_symlink.cpp
 * 2022-06-01 K.OHWADA
 */

// ln -s regular.txt symlink.txt
// g++  is_symlink.cpp -o bin/is_symlink -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/is_symlink.html

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
    string symlink("symlink.txt");


  // (1)
// check if it is a symbolic link using the obtained file status
  assert(fs::is_symlink(fs::symlink_status(symlink)));

  // (2)
// specify the path and check if it is a symbolic link.
  assert(fs::is_symlink(symlink));
  assert(!fs::is_symlink(file));
  assert(!fs::is_symlink(path));

  // (3)
  // receive error information as error_code instead of exception
  std::error_code ec;
  bool result = fs::is_symlink(symlink, ec);
  assert(!ec);
  assert(result);

    cout << "successful" << endl;

    return 0;
}

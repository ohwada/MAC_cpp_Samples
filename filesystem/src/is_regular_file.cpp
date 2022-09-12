/**
 *  is_regular_file.cpp 
 * 2022-06-01 K.OHWADA
 */

// ln -s regular.txt symlink.txt
// g++ is_regular_file.cpp  -o bin/is_file -std=c++17
// https://cpprefjp.github.io/reference/filesystem/is_regular_file.html

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


  // fs::create_symlink("regular.txt", "regular.symlink");

  // (1)
// use the obtained file status to check if it is a regular file
  assert(fs::is_regular_file(fs::status(file)));

  // (2)
// specify the path and check if it is a regular file.
  // symbolic links are determined by the destination file
  assert(fs::is_regular_file(file));
  assert(fs::is_regular_file(symlink));
  assert(!fs::is_regular_file(path));

  // (3)
// receive error information as error_code instead of exception
  std::error_code ec;
  bool result = fs::is_regular_file(file, ec);
  assert(!ec);
  assert(result);

    cout << "successful" << endl;

    return 0;
}



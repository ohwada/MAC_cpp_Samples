/**
 *  path.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ path.cpp -o bin/path  -std=c++17 
// reference : https://cpprefjp.github.io/reference/filesystem/path.html

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


/**
 *  main
 */
int main()
{
  fs::path p = "/a/b/c.txt";

std::cout <<  p << std::endl;

// extract From the path,  the directory without the file name, 
// the file name, file name without extension, extension
  std::cout << "directory : " << p.parent_path() << std::endl;
  std::cout << "filename  : " << p.filename() << std::endl;
  std::cout << "stem      : " << p.stem() << std::endl;
  std::cout << "extension : " << p.extension() << std::endl;

// determine if the path is absolute or relative
  if (p.is_absolute()) {
    std::cout << p << " is absolute path" << std::endl;
  }
  else {
    std::cout << p << " is relative path" << std::endl;
  }

    return 0;
}


// "/a/b/c.txt"
// directory : "/a/b"
// filename  : "c.txt"
// stem      : "c"
// extension : ".txt"
// "/a/b/c.txt" is absolute path



/**
 *   file_size.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  file_size.cpp -o bin/file_size  -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/file_size.html

 #include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;


/**
 *   main
 */
int main()
{
    string fname("temp.txt");

  {
    std::ofstream file{fname, std::ios::binary};
    std::uint32_t value = 42;
    file.write(reinterpret_cast<char*>(&value), sizeof(value));
  }

  std::uintmax_t size = fs::file_size(fname);
  assert(size == 4);

    cout << "successful" << endl;

    return 0;
}


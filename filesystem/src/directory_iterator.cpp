/**
 *  directory_iterator.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ directory_iterator.cpp -o bin/directory_iterator -std=c++17 
// reference : https://cpprefjp.github.io/reference/filesystem/directory_iterator.html

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


/**
 *  main
 */
int main()
{
    string path(".");

  // output all files under the directory
  for (const fs::directory_entry& x : fs::directory_iterator( path)) {
    cout << x.path() << endl;
  }

    return 0;
}

/**
 *  exists.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ exists.cpp -o bin/exists -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/exists.html


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
    string file("regular.txt");
    string path("sample2");


  // (1)
  // check the existence of the file using the obtained file state
  assert(fs::exists(fs::status(file)));

  // (2)
// confirm existence of file/directory by specifying path
  assert(fs::exists(file));
  assert(fs::exists(path));

  // (3)
// Receive error information as error_code instead of exception
  std::error_code ec;
  bool result = fs::exists(file, ec);
  assert(!ec);
  assert(result);

    cout << "successful" << endl;

    return 0;
}


/**
 *  remove.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ remove.cpp -o bin/remove -std=c++17 
// reference : https://cpprefjp.github.io/reference/filesystem/remove.html

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;


/**
 * main
 */
int main()
{

string file("temp.txt");
string path("empty_dir");

  std::ofstream{file};
  fs::create_directory(path);

  fs::remove(file);
  fs::remove(path);


// remove files that don't exist.
// returns false instead of an error
  bool result = fs::remove("not_exist.file");
  assert(!result);

  assert(!fs::exists(file));
  assert(!fs::exists(path));

    cout << "successful" << endl;

    return 0;
}



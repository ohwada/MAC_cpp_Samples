/**
 *   rename.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  rename.cpp -o bin/rename  -std=c++17 
// reference : https://cpprefjp.github.io/reference/filesystem/rename.html

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;


/**
 *  main
 */
int main()
{

// rename file
  {
    std::ofstream{"a.txt"};

// rename "a.txt" to "b.txt"
    fs::rename("a.txt", "b.txt");

    assert(!fs::exists("a.txt"));
    assert(fs::exists("b.txt"));
  }

// rename directory
  {
// create a directory containing the files
    fs::create_directory("a_dir");
    std::ofstream{"a_dir/regular.txt"};

// rename "a_dir" directory to "b_dir" directory
    fs::rename("a_dir", "b_dir");

    assert(!fs::exists("a_dir"));
    assert(fs::exists("b_dir"));
    assert(fs::exists("b_dir/regular.txt"));
  }

// rename the symlink
  {
    std::ofstream{"base.txt"};
    fs::create_symlink("base.txt", "base.symlink");

    fs::rename("base.symlink", "base_symlink.txt");

    assert(!fs::exists("base.symlink"));
    assert(fs::exists("base_symlink.txt"));
  }

    cout << "successful" << endl;

    return 0;
}



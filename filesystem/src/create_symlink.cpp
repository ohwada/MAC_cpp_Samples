/**
 *  create_symlink.cpp
 * 2022-06-01 K.OHWADA
 */
// g++ create_symlink.cpp -o bin/create_symlink -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/create_symlink.html

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

    string file("regular.txt");
    string symlink("new_symlink.txt");


// create a symlink to "regular.txt" as "new_symlink.txt" file
  fs::create_symlink(file, symlink);

  assert(fs::exists(symlink));
  assert(fs::is_symlink(symlink));

    cout << "creted: " << symlink << endl;

    return 0;
}

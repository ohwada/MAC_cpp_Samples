/**
 *  read_symlink.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ read_symlink.cpp -o bin/read_symlink -std=c++17 
// reference : https://cpprefjp.github.io/reference/filesystem/read_symlink.html

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
	string file("temp.txt");
	string symlink("temp_synlink.txt");

  ofstream{file};
  fs::create_symlink(file, symlink);

  fs::path result = fs::read_symlink(symlink);
  cout << result << endl;

    assert(file == result);

    cout << "successful" << endl;

	return 0;
}

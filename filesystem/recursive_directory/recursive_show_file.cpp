/**
 *  recursive_show_file.cpp
 * 2022-06-01 K.OHWADA
 */

// Show file in directory recursivily
// reference : https://cpprefjp.github.io/reference/filesystem/recursive_directory_iterator.html

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


/**
 *  main
 */
int main(int argc, char* argv[])
{
 
 	string path(".");
    
   
    if(argc == 2){
        path = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <dir> " << endl;
    }

   cout << path << endl;
   
// recursively output all files contained in the "dir_a" directory
  for (const fs::directory_entry& x : fs::recursive_directory_iterator(path)) {
    cout << x.path() << endl;
  } // for

    return 0;
}


// "./test"
// "./test/wct123.txt"
// "./test/.DS_Store"
// "./test/wctABC.tmp"
// "./test/1st"


/**
 * recursive_file_size.cpp
 * 2022-06-01 K.OHWADA
 */

// Computing the size of a directory
// original ; https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter04/problem_35/main.cpp

#include <iostream>
#include <numeric>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;


/**
 * get_directory_size
 */
std::uintmax_t get_directory_size(
   fs::path const & dir )
{
   auto iterator = fs::recursive_directory_iterator(dir);

   return std::accumulate(
      fs::begin(iterator), fs::end(iterator),
      0ull,
      [](std::uintmax_t const total,
         fs::directory_entry const & entry) {
        std::cout << entry.path() << std::endl;
      return total + (fs::is_regular_file(entry) ?
         fs::file_size(entry.path()) : 0);
   });
}

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
 
 	string path(".");

    if(argc == 2){
        path = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <path> " << endl;
    }

   cout <<  path << endl;

    std::uintmax_t size = get_directory_size(path);

   cout << "Size: " << size << endl;

    return 0;
}


// "./test/wct123.txt"
// "./test/.DS_Store"
// "./test/wctABC.tmp"
// "./test/1st"
// Size: 245035


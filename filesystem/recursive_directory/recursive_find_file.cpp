/**
 * recursive_find_file.cpp
 * 2022-06-01 K.OHWADA
 */

// Finding files in a directory that match a regular expression
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter04/problem_37/main.cpp

#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;


/**
 *  find_files
 */
std::vector<fs::directory_entry> find_files(
   fs::path const & path,
   std::string_view regex)
{
   std::vector<fs::directory_entry> result;
   std::regex rx(regex.data());

   std::copy_if(
      fs::recursive_directory_iterator(path),
      fs::recursive_directory_iterator(),
      std::back_inserter(result),
      [&rx](fs::directory_entry const & entry) {
         return fs::is_regular_file(entry.path()) &&
                std::regex_match(entry.path().filename().string(), rx);
      });

   return result;
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

   auto pattern = R"(wct[0-9a-zA-Z]{3}\.tmp)";
   auto result = find_files(path, pattern);

   for (auto const & entry : result)
   {
      std::cout << entry.path().string() << std::endl;
   } // for

    return 0;
}


// ./test/wctABC.tmp
// ./test/1st/wctDEF.tmp
// ./test/1st/2nd/wctXYZ.tmp
// ./test/1st/2nd/wct789.tmp
// ./test/1st/wct456.tmp
// ./test/wct123.tmp


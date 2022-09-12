/**
 *  status.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ status.cpp -o bin/status -std=c++17
// https://cpprefjp.github.io/reference/filesystem/status.html

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
  
  // (1)
// throw std::filesystem::filesystem_error exception 
// if the file is not found
  {
    try {
      fs::file_status status = fs::status(file);
      assert(status.type() == fs::file_type::regular);
      assert((status.permissions() & fs::perms::owner_write) != fs::perms::none);
    }
    catch (fs::filesystem_error& fe) {
      cout << fe.what() << endl;
    }
  }

  // (2)
// don't throw exceptions
  {
    std::error_code ec;
    fs::file_status status = fs::status(file, ec);
    if (ec) {
      cout << ec.message() << endl;
    } else {
      assert(status.type() == fs::file_type::regular);
      assert((status.permissions() & fs::perms::owner_write) != fs::perms::none);
    }
  }

    cout << "successful" << endl;

    return 0;
}

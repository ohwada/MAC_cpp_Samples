/**
 *   last_write_time.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  last_write_time.cpp -o bin/last_write_time  -std=c++17
// reference : https://cpprefjp.github.io/reference/filesystem/last_write_time.html

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <iomanip>

namespace fs = std::filesystem;


/**
 * print_datetime
 */
void print_datetime(const char* name, fs::file_time_type tp)
{
  namespace chrono = std::chrono;
  auto sec = chrono::duration_cast<chrono::seconds>(tp.time_since_epoch());

  std::time_t t = sec.count();
  const std::tm* lt = std::localtime(&t);
    std::cout <<  std::put_time(lt, "%c") << std::endl;
}


using namespace std;


/**
 * main
 */
int main()
{
    string file("temp.txt");
    string path("dir_temp");

  std::ofstream{ file };
  fs::create_directory(path);


// get the last modified time of the file/directory
  fs::file_time_type file_time = fs::last_write_time(file);
  fs::file_time_type dir_time = fs::last_write_time(path);


  print_datetime("file time", file_time);
  print_datetime("dir time", dir_time);

  
// set the current date and time as the last modified date and time of the file
  fs::last_write_time(file, fs::file_time_type::clock::now());

 cout << "successful" << endl;

    return 0;
}

/**
 *  temporary_log.cpp
 * 2022-06-01 K.OHWADA
 */

 // Temporary log files
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter04/problem_38/main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <uuid/uuid.h>

namespace fs = std::filesystem;


/**
 *  gen_uuid_random
 */
std::string gen_uuid_random()
{
	uuid_t value;
	uuid_generate(value);

	uuid_string_t result;
	uuid_unparse_upper(value, result);

    return std::string(result);
}


/**
 *  class logger
 */
class logger
{
   fs::path       logpath;
   std::ofstream  logfile;
public:
   logger()
   {
      auto name = gen_uuid_random();

      logpath = fs::temp_directory_path() / (name + ".tmp");
      logfile.open(logpath.c_str(), std::ios::out|std::ios::trunc);
      std::cout << logpath << std::endl;
   }

   ~logger() noexcept
   {
      try {
         if(logfile.is_open())
            logfile.close();
         if (!logpath.empty())
            fs::remove(logpath);
      }
      catch (...) {
      }
   }

   void persist(fs::path const & path)
   {
      logfile.close();
      fs::rename(logpath, path);
      logpath.clear();
   }

   logger& operator<<(std::string_view message)
   {
      logfile << message.data() << '\n';
      return *this;
   }
};


using namespace std;


/**
 *  main
 */
int main()
{
    string file("lastlog.txt");

   logger log;
   try
   {
      log << "this is a line" << "and this is another one";

      throw std::runtime_error("error");
   }
   catch (...)
   {
      log.persist(file);
   }

    cout << "created: " << file << endl;

    return 0;
}


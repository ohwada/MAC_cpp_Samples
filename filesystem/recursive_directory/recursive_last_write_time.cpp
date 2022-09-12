/**
 * recursive_last_write_time.cpp
 * 2022-06-01 K.OHWADA
 */


// Showing files older than a given date
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter04/problem_36/main.cpp

#include <iostream>
#include <chrono>
#  include <filesystem>

namespace fs = std::filesystem;
namespace ch = std::chrono;


/**
 * get_datetime
 */
std::string get_datetime(fs::file_time_type tp)
{
  auto sec = ch::duration_cast<ch::seconds>(tp.time_since_epoch());

  std::time_t t = sec.count();

    const int BUFSIZE = 64;
    char buf[BUFSIZE];
    strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S %Z", std::localtime(&t) );

    std::string str(buf);

    return str;
}


/**
 * is_older_than
 */
template <typename Duration>
bool is_older_than(fs::file_time_type lastwrite, Duration const duration)
{
    auto ftimeduration = lastwrite.time_since_epoch();

   auto nowduration = (ch::system_clock::now() - duration).time_since_epoch();

   return ch::duration_cast<Duration>(nowduration - ftimeduration).count() > 0;
}


/**
 *  remove_files_older_than
 */
template <typename Duration>
void remove_files_older_than(fs::path const & path, Duration const duration,  bool is_remove)
{
   try
   {
      if (fs::exists(path))
      {
        auto lastwrite = fs::last_write_time(path);
        auto str_time = get_datetime(lastwrite);
         if (is_older_than( lastwrite, duration))
         {
            std::cout << path << " ( " << str_time << " ) " << std::endl;
            if(is_remove){
                fs::remove(path);
                std::cout << "remove:" << path << std::endl;
            }
          }
         else if(fs::is_directory(path))
         {
            for (auto const & entry : fs::directory_iterator(path))
            {
               remove_files_older_than(entry.path(), duration, is_remove);
            } // for
         }
      }
   }
   catch (std::exception const & ex)
   {
      std::cerr << ex.what() << std::endl;
   }
}


using namespace std;
using namespace std::chrono_literals;


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

    bool is_remove = false;

   remove_files_older_than(path, 1h + 20min,  is_remove);

    return 0;
}


// "./test" ( 2022-08-30 21:02:17 JST ) 
// "./bin/file_size" ( 2022-08-30 23:15:09 JST ) 
// "./recursive_delete_file.cpp" ( 2022-08-31 00:10:27 JST ) 



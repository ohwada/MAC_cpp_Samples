/**
 *  image.cpp
 * 2022-06-01 K.OHWADA
 */

// chang log
// add get command

// Handling movie images in an SQLite database  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_87/main.cpp


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "sqlite3.h"

#include "sqlite_modern_cpp.h"
#include "movies.h"

#include "parse_filename.hpp"
#include "file_util.hpp"


/**
 *  get_movies
 */
movie_list get_movies(std::string_view title, sqlite::database & db)
{
   movie_list movies;

   db << R"(select rowid, * from movies where title=?;)"
      << title.data()
      >> [&movies](sqlite3_int64 const rowid, std::string const & title,
         int const year, int const length)
   {
      movies.emplace_back(movie{
         static_cast<unsigned int>(rowid),
         title,
         year,
         static_cast<unsigned int>(length),
         {},
         {},
         {}
         });
   };

   return movies;
}


/**
 *  add_media
 */
bool add_media(sqlite_int64 const movieid,
               std::string_view name,
               std::string_view description,
               std::vector<char> content,
               sqlite::database & db)
{
   try
   {
      db << "insert into media values(?,?,?,?)"
         << movieid
         << name.data()
         << description.data()
         << content;
         
      return true;
   }
   catch (...) { return false; }
}


/**
 *  get_media
 */
media_list get_media(sqlite_int64 const movieid,
                     sqlite::database & db)
{
   media_list list;

   db << "select rowid, * from media where movieid = ?;"
      << movieid
      >> [&list](sqlite_int64 const rowid, 
            sqlite_int64 const movieid, 
            std::string const & name,
            std::string const text,
            std::vector<char> const & blob
         )
         {
      list.emplace_back(media{
         static_cast<unsigned int>(rowid),
         static_cast<unsigned int>(movieid),
         name,
               text,
               blob});
         };

   return list;
}


/**
 *  delete_media
 */
bool delete_media(sqlite_int64 const mediaid,
                  sqlite::database & db)
{
   try
   {
      db << "delete from media where rowid = ?;"
         << mediaid;

      return true;
   }
   catch (...) { return false; }
}


/**
 *  split
 */
std::vector<std::string> split(std::string text, char const delimiter)
{
   auto sstr = std::stringstream{ text };
   auto tokens = std::vector<std::string>{};
   auto token = std::string{};
   while (std::getline(sstr, token, delimiter))
   {
      if (!token.empty()) tokens.push_back(token);
   }
   return tokens;
}


/**
 *  starts_with
 */
inline bool starts_with(std::string_view text, std::string_view part)
{
   return text.find(part) == 0;
}


/**
 *   trim
 */
inline std::string trim(std::string_view text)
{
   auto first{ text.find_first_not_of(' ') };
   auto last{ text.find_last_not_of(' ') };
   return text.substr(first, (last - first + 1)).data();
}


/**
 *  load_image
 */
std::vector<char> load_image(std::string filepath)
{
   std::vector<char> data;

   std::ifstream ifile(filepath.data(), std::ios::binary | std::ios::ate);
  
   if (ifile)
   {
      auto size = ifile.tellg();
      ifile.seekg(0, std::ios::beg);

      data.resize(static_cast<size_t>(size));
      ifile.read(reinterpret_cast<char*>(data.data()), size);
   } else {
        std::cout << "cannot open: " << filepath << std::endl;
    }

   return data;
}


/**
 *  run_find
 */
void run_find(std::string_view line, sqlite::database & db)
{
   auto title = trim(line.substr(5));

   auto movies = get_movies(title, db);
   if(movies.empty())
      std::cout << "empty" << std::endl;      
   else
   {
      for (auto m : movies)
      {
         std::cout
            << m.id << " | "
            << m.title << " | "
            << m.year << " | "
            << m.length << "min"
            << std::endl;
      }
   }      
}


/**
 *  run_list
 */
void run_list(std::string_view line, sqlite::database & db)
{
   auto movieid = std::stoi(trim(line.substr(5)));
   if (movieid > 0)
   {
      auto list = get_media(movieid, db);
      if (list.empty())
      {
         std::cout << "empty" << std::endl;
      }
      else
      {
         for (auto const & m : list)
         {
            std::cout
               << m.id << " | "
               << m.movie_id << " | "
               << m.name << " | "
               << m.text << " | "
               << m.blob.size() << " bytes"
               << std::endl;
         }
      }
   }
   else
      std::cout << "input error" << std::endl;
}


/**
 *   run_add
 */
void run_add(std::string_view line, sqlite::database & db)
{
   auto parts = split(trim(line.substr(4)), ',');
   if (parts.size() == 3)
   {
      auto movieid = std::stoi( trim(parts[0]) );

      auto path = trim(parts[1]);

      auto desc = trim(parts[2]);

      auto name =  getFileNameWithExt(path);

      auto content = load_image(path);
    if( content.size() == 0 ) {
         std::cout << "cannot load: " << path << std::endl;
        return;
    }

      bool success = add_media(movieid, name, desc, content, db);
      if (success) {
         std::cout << "added" << std::endl;
         std::cout << "movieid: " << movieid<< std::endl;
         std::cout << "name: " << name << std::endl;
         std::cout << " desc: " <<  desc << std::endl;
      } else {
         std::cout << "failed" << std::endl;
        }
   }
   else
      std::cout << "input error" << std::endl;
}


/**
 *  run_del
 */
void run_del(std::string_view line, sqlite::database & db)
{
   auto mediaid = std::stoi(trim(line.substr(4)));
   if (mediaid > 0)
   {
      auto success = delete_media(mediaid, db);
      if (success)
         std::cout << "deleted" << std::endl;
      else
         std::cout << "failed" << std::endl;
   }
   else
      std::cout << "input error" << std::endl;
}


/**
 *  run_get
 */
void run_get(std::string_view line, sqlite::database & db)
{

    std::string dir("out");
   auto movieid = std::stoi(trim(line.substr(4)));
   if (movieid > 0)
   {
      auto list = get_media(movieid, db);
      if (list.empty())
      {
         std::cout << "empty" << std::endl;
      }
      else
      {
            auto m = list[0];

            std::cout
               << m.id << " | "
               << m.movie_id << " | "
               << m.name << " | "
               << m.text
               << std::endl;

            auto fpath = make_path(dir, m.name);
            bool ret = writeBinaryFile1(fpath, m.blob);
            if(ret){
                std::cout << "saved to " << fpath << std::endl;
            } else {
                std::cerr << " writeBinaryFile1 failed: " << fpath << std::endl;
            }
   
      }
   }
   else
      std::cout << "input error" << std::endl;
}


/**
 *  print_commands
 */
void print_commands()
{
   std::cout
      << "find <title>                        finds a movie ID\n"
      << "list <movieid>                      lists the images of a movie\n"
      << "add <movieid>,<path>,<description>  adds a new image\n"
      << "del <imageid>                       delete an image\n"
      << "get <imageid> get an image and save to file \n"
      << "help                                shows available commands\n"
      << "exit                                exists the application\n";
}


/**
 *  main
 */
int main()
{
   try
   {
      sqlite::database db(R"(movies.db)");

    std::cout << "input command(eg: help)" << std::endl;

      while (true)
      {
         std::string line;
         std::getline(std::cin, line);

         if (line == "help") print_commands();
         else if (line == "exit") break;
         else
         {
            if (starts_with(line, "find"))
               run_find(line, db);
            else if (starts_with(line, "list"))
               run_list(line, db);
            else if (starts_with(line, "add"))
               run_add(line, db);
            else if (starts_with(line, "del"))
               run_del(line, db);
            else if (starts_with(line, "get"))
               run_get(line, db);
            else
               std::cout << "unknown command" << std::endl;
         }

         std::cout << std::endl;
      }
   }
   catch (sqlite::sqlite_exception const & e)
   {
      std::cerr << e.get_code() << ": " << e.what() << " during "
                << e.get_sql() << std::endl;
   }
   catch (std::exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }

    return 0;
}

/**
 * movie.cpp
* show Movie Title
 * 2022-06-01 K.OHWADA
 */

// g++ movie.cpp -o movie -std=c++11
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_76/main.cpp
#include <iostream>
#include <string_view>
#include <fstream>
#include <assert.h>
#include <nlohmann/json.hpp>
#include "movies.h"

using json = nlohmann::json;


/**
 * deserialize
 */
movie_list deserialize(std::string_view filepath)
{
   movie_list movies;

   std::ifstream ifile(filepath.data());
   if (ifile.is_open())
   {
      json jdata;

      try
      {
         ifile >> jdata;

         if (jdata.is_object())
         {
            for (auto & element : jdata.at("movies"))
            {
               movie m;

               m.id = element.at("id").get<unsigned int>();
               m.title = element.at("title").get<std::string>();
               m.year = element.at("year").get<unsigned int>();
               m.length = element.at("length").get<unsigned int>();

               for (auto & role : element.at("cast"))
               {
                  m.cast.push_back(casting_role{
                     role.at("star").get<std::string>(),
                     role.at("name").get<std::string>() });
               }

               for (auto & director : element.at("directors"))
               {
                  m.directors.push_back(director);
               }

               for (auto & writer : element.at("writers"))
               {
                  m.writers.push_back(writer);
               }

               movies.push_back(std::move(m));
            }
         }
      }
      catch (std::exception const & ex)
      {
         std::cout << ex.what() << std::endl;
      }
   } else {
         std::cout <<  "cannot open: " << filepath << std::endl;
    }

   return movies;
}


/**
 * main
 */
int main()
{
   auto movies = deserialize("movies.json");

   assert(movies.size() == 2);
   assert(movies[0].title == "The Matrix");
   assert(movies[1].title == "Forrest Gump");

for(auto m: movies){
    std::cout << m.title << std::endl;
}

    return 0;
}

// The Matrix
// Forrest Gump

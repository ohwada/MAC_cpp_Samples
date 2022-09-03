/**
 * movie1.cpp
 * 2022-06-01 K.OHWADA
 */

// Serializing and deserializing data to/from XML  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_73/main.cpp

#include <iostream>
#include <string>
#include <assert.h>

#include "pugixml.hpp"
#include "movies.h"


/**
 *  serialize
 */
void serialize(movie_list const & movies, std::string filepath)
{
   pugi::xml_document doc;

   auto root = doc.append_child("movies");

   for (auto const & m : movies)
   {
      auto movie_node = root.append_child("movie");

      movie_node.append_attribute("id").set_value(m.id);
      movie_node.append_attribute("title").set_value(m.title.c_str());
      movie_node.append_attribute("year").set_value(m.year);
      movie_node.append_attribute("length").set_value(m.length);

      auto cast_node = movie_node.append_child("cast");
      for (auto const & c : m.cast)
      {
         auto node = cast_node.append_child("role");
         node.append_attribute("star").set_value(c.actor.c_str());
         node.append_attribute("name").set_value(c.role.c_str());
      }

      auto directors_node = movie_node.append_child("directors");
      for (auto const & director : m.directors)
      {
         directors_node.append_child("director")
                       .append_attribute("name").set_value(director.c_str());
      }

      auto writers_node = movie_node.append_child("writers");
      for (auto const & writer : m.writers)
      {
         writers_node.append_child("writer")
                     .append_attribute("name").set_value(writer.c_str());
      }
   }

   doc.save_file(filepath.data());
}


/**
 * deserialize
 */
movie_list deserialize(std::string filepath)
{
   pugi::xml_document doc;
   movie_list movies;

   auto result = doc.load_file(filepath.data());
   if (result)
   {
      auto root = doc.child("movies");
      for (auto movie_node = root.child("movie");
         movie_node;
         movie_node = movie_node.next_sibling("movie"))
      {
         movie m;
         m.id = movie_node.attribute("id").as_uint();
         m.title = movie_node.attribute("title").as_string();
         m.year = movie_node.attribute("year").as_uint();
         m.length = movie_node.attribute("length").as_uint();

         for (auto role_node : movie_node.child("cast").children("role"))
         {
            m.cast.push_back(casting_role{
               role_node.attribute("star").as_string(),
               role_node.attribute("name").as_string()
               });
         }

         for (auto director_node : movie_node.child("directors").children("director"))
         {
            m.directors.push_back(director_node.attribute("name").as_string());
         }

         for (auto writer_node : movie_node.child("writers").children("writer"))
         {
            m.writers.push_back(writer_node.attribute("name").as_string());
         }

         movies.push_back(m);
      }
   }

   return movies;
}


/**
 *  movie_list movies
 */
   const movie_list MOVIES
   {
      {
         11001,
         "The Matrix",
         1999,
         196,
         {
            {"Keanu Reeves", "Neo"},
            {"Laurence Fishburne", "Morpheus"},
            {"Carrie-Anne Moss", "Trinity"}, 
            {"Hugo Weaving", "Agent Smith"}
         },
         {"Lana Wachowski", "Lilly Wachowski"},
         {"Lana Wachowski", "Lilly Wachowski"},
      },
      {
         9871,
         "Forrest Gump",
         1994,
         202,
         {
            {"Tom Hanks", "Forrest Gump"},
            {"Sally Field", "Mrs. Gump"},
            {"Robin Wright","Jenny Curran"},
            {"Mykelti Williamson","Bubba Blue"}
         },
         {"Robert Zemeckis"},
         {"Winston Groom", "Eric Roth"},
      }
   };

using namespace std;


/**
 * main
 */
int main()
{
const string FILE("movies.xml");

   serialize(MOVIES,  FILE);   

    cout << "created: " << FILE << endl;

   auto result = deserialize(FILE);

   assert(result.size() == 2);
   assert(result[0].title == "The Matrix");
   assert(result[1].title == "Forrest Gump");

    for(auto x: result) {
        cout << x.title << endl;
    } // for

    return 0;
}

// created: movies.xml
// The Matrix
// Forrest Gump

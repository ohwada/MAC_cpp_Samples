#pragma once
/**
 * movie.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/include/movies.h
#include <string>
#include <vector>


/**
 * struct casting_role
 */
struct casting_role
{
   std::string actor;
   std::string role;
};


/**
 * struct movie
 */
struct movie
{
   unsigned int   id;
   std::string    title;
   int            year;
   unsigned int   length;

   std::vector<casting_role>  cast;
   std::vector<std::string>   directors;
   std::vector<std::string>   writers;
};


/**
 * struct media
 */
struct media
{
   unsigned int            id;
   unsigned int            movie_id;
   std::string             name;
   std::string   text;
   std::vector<char>       blob;
};

using movie_list = std::vector<movie>;
using media_list = std::vector<media>;
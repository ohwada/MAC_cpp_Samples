#pragma once
/**
 * movie_c.h
 * 2022-06-01 K.OHWADA
 */

const int NUM = 10;
const int BUFSIZE = 256;


/**
 * struct casting_role
 */
struct casting_role
{
   char star[BUFSIZE];
   char role[BUFSIZE];
};


/**
 * struct movie
 */
struct movie
{
   unsigned int   id;
   char    title[BUFSIZE];
   int            year;
   unsigned int   length;
   struct casting_role  cast[NUM];
   char directors[NUM][BUFSIZE];
   char   writers[NUM][BUFSIZE];
    int num_cast;
    int num_director;
    int num_writer;
};


/**
 * struct media
 */
struct media
{
   unsigned int            id;
   unsigned int            movie_id;
   char             name[BUFSIZE];
   char   text[BUFSIZE];
};

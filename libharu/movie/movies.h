#pragma once
/**
 * movie.h
 * 2022-06-01 K.OHWADA
 */


const int BUFSIZE = 256;


/**
 * struct movie
 */
struct movie
{
   unsigned int   id;
   char    title[BUFSIZE];
   int            year;
   unsigned int   length;
  };


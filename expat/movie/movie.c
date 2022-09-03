 /**
 * movie.c
 * 2022-06-01 K.OHWADA
 */

// deserializing data from movie XML  
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_73/main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <expat.h>
#include <assert.h>
#include "movies.h"


 /**
 * typedef enum
 */
typedef enum {
DOCUMENT,
MOVIES,
MOVIE,
CAST, 
ROLE,
DIRECTORS,
DIRECTOR,
WRITERS,
WRITER
} element;

element current = DOCUMENT;

const char NUL = '\0';

const int NUM_MOVIES = 10;
struct movie movies[NUM_MOVIES];

int num_movie = 0;

int cnt_movie = 0;
int cnt_role = 0;
int cnt_director = 0;
int cnt_writer = 0;


 /**
 * elementStart
 */
static void XMLCALL
elementStart(void *user_data, const XML_Char *el, const XML_Char *attr[]) 
{
    const int BUFSIZE = 256;
    char id[BUFSIZE];
    char title[BUFSIZE];
    char year[BUFSIZE];
    char length[BUFSIZE];
    char star[BUFSIZE];
    char name[BUFSIZE];

    for(int i=0; i<BUFSIZE; i++){
        id[i] = NUL;
        title[i] = NUL;
        year[i] = NUL;
        length[i] = NUL;
        star[i] = NUL;
        name[i] = NUL;
    }

    if (strcmp(el, "movies") == 0){
        current = MOVIES;
        cnt_movie = -1;
    }
    if (strcmp(el, "movie") == 0){
        current = MOVIE;
        cnt_movie++;
    }
   if (strcmp(el, "cast") == 0){
            current = CAST;
            cnt_role = -1;
    }
   if (strcmp(el, "role") == 0){
            current = ROLE;
            cnt_role++;
    }
   if (strcmp(el, "directors") == 0){
            current = DIRECTORS;
            cnt_director = -1;
    }
   if (strcmp(el, "director") == 0){
            current = DIRECTOR;
            cnt_director++;
    }
   if (strcmp(el, "writers") == 0){
            current = WRITERS;
            cnt_writer = -1;
    }
   if (strcmp(el, "writer") == 0){
            current = WRITER;
            cnt_writer++;
    }


    bool is_id = false;
    bool is_title = false;
    bool is_year = false;
    bool is_length = false;
    bool is_star = false;
    bool is_name = false;

    int i;
    for(i=0; i<10; i++){
        if(attr[i] == NULL){
            break;
        }
        if(is_id){
            strcpy(id, attr[i]);
            is_id = false;
        }
        if(is_title){
            strcpy(title, attr[i]);
            is_title = false;
        }
        if(is_year){
            strcpy(year, attr[i]);
            is_year = false;
        }
        if(is_length){
            strcpy(length, attr[i]);
            is_id = false;
        }
   if(is_star){
            strcpy(star, attr[i]);
            is_star = false;
        }
   if(is_name){
            strcpy(name, attr[i]);
            is_name = false;
        }

        if (strcmp(attr[i], "id") == 0){
            is_id = true;
        }
        if (strcmp(attr[i], "title") == 0){
            is_title = true;
        }
        if (strcmp(attr[i], "year") == 0){
            is_year = true;
        }
        if (strcmp(attr[i], "length") == 0){
            is_length = true;
        }
      if (strcmp(attr[i], "star") == 0){
            is_star = true;
        }
      if (strcmp(attr[i], "name") == 0){
            is_name = true;
        }
    } // for


    if(current == MOVIE){
        movies[cnt_movie].id = atoi(id);
        movies[cnt_movie].year = atoi(year);
        movies[cnt_movie].length = atoi(length);
        strcpy( movies[cnt_movie].title, title);
    }

    if(current == ROLE){
        strcpy( movies[cnt_movie].cast[cnt_role].star, star);
        strcpy( movies[cnt_movie].cast[cnt_role].role, name);
    }

   if(current == DIRECTOR){
        strcpy( movies[cnt_movie].directors[cnt_director], name);
    }

   if(current == WRITER){
        strcpy( movies[cnt_movie].writers[cnt_writer], name);
    }

#ifdef DEBUG
    if ( strlen(id) > 0 ){
        printf("id: %s \n", id);
    }
    if ( strlen(title) > 0 ){
        printf("title: %s \n", title);
    }
    if ( strlen(year) > 0 ){
        printf("year: %s \n", year);
    }
    if ( strlen(length) > 0 ){
        printf("length: %s \n", length);
    }
    if ( strlen(star) > 0 ){
        printf("star: %s \n", star);
    }
    if ( strlen(name) > 0 ){
        printf("name: %s \n", name);
    }
#endif

return;
}


 /**
 * elementEnd
 */
static void XMLCALL
elementEnd(void *user_data, const XML_Char *el) 
{

    if (strcmp(el, "movies") == 0){
        num_movie = cnt_movie+1;
    }
    if (strcmp(el, "cast") == 0){
        movies[cnt_movie]. num_cast = cnt_role+1;
    }
    if (strcmp(el, "directors") == 0){
       movies[cnt_movie]. num_director = cnt_director+1;
    }
    if (strcmp(el, "writers") == 0){
       movies[cnt_movie]. num_writer = cnt_writer+1;
    }

return;
}


 /**
 * elementData
 */
static void XMLCALL
elementData(void *user_data, const XML_Char *data, int data_size) 
{
    // none
}


 /**
 * dump
 */
void dump(struct movie m)
{
    printf("\n");

    printf("id: %d \n", m.id);
    printf("title: %s \n", m.title);
    printf("year: %d \n", m.year);
    printf("length: %d \n", m.length);

        printf("cast: \n");
    for(int i=0; i<m.num_cast; i++){
        printf("star: %s \n", m.cast[i].star);
        printf("role: %s \n", m.cast[i].role);
    }

     printf("director: \n");
    for(int i=0; i<m.num_director; i++){
        printf("%s \n", m.directors[i]);
    }

     printf("writer: \n");
    for(int i=0; i<m.num_writer; i++){
        printf("%s \n", m.writers[i]);
    }

return;
}


 /**
 * main
 */
int main(int argc, char *argv[])
{
const int BUFSIZE = 102400;
  char buf[BUFSIZE];

const char* FILEPATH = "movies.xml";



  int done;
  XML_Parser parser;

  if ((parser = XML_ParserCreate(NULL)) == NULL) {
    fprintf(stderr, "Parser Creation Error.\n");
    return 1;
  }

FILE *fp;
fp = fopen(FILEPATH, "r");
if(!fp){
    fprintf(stderr, "cannot open: %s \n", FILEPATH);
}

  XML_SetElementHandler(parser, elementStart, elementEnd);
  XML_SetCharacterDataHandler(parser, elementData);

  do {
    size_t len = fread(buf, sizeof(char), BUFSIZE, fp);
    if (len == 0) {
      fprintf(stderr, "File Error.\n");
      return 1;
    }

    done = len < sizeof(buf);
    if (XML_Parse(parser, buf, (int)len, done) == XML_STATUS_ERROR) {
      fprintf(stderr, "Parse Error.\n");
      return 1;      
    }
  } while(!done);

  XML_ParserFree(parser);

   assert(num_movie == 2);
   assert( strcmp(movies[0].title, "The Matrix") == 0 );
   assert( strcmp( movies[1].title, "Forrest Gump") == 0 );

    for(int i=0; i<num_movie; i++)
    {
        dump(movies[i]);
    }

  return 0;
}


// id: 11001 
// title: The Matrix 
// year: 1999 
// length: 196 




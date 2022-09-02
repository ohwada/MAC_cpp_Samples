/**
 * movie.c
 * 2022-06-01 K.OHWADA
 */

// Reading movies from an SQLite database  
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_85/main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sqlite3.h"
#include "movies.h"


const int NUM_MOVIES = 10;
struct movie movies[NUM_MOVIES];

const int NUM_PERSONS = 20;
char persons[NUM_PERSONS][BUFSIZE];

int num_movie = 0;


/**
 *  select_persons
 */
bool select_persons(sqlite3 *db )
{
    sqlite3_stmt *stmt;
    int rc; //result codes

// generate prepared statement
    rc = sqlite3_prepare_v2(db,"SELECT  rowid, name FROM persons", -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }
    
char name[BUFSIZE];

int rowid;

// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        rowid = sqlite3_column_int(stmt, 0);
        strcpy( name, (char *)sqlite3_column_text(stmt, 1) );
        //printf("rowid: %d \n", rowid);
        //printf("name: %s \n", name);
        //printf("\n");
        strcpy( persons[rowid], name);
        rc = sqlite3_step(stmt);
    } // while

// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}


/**
 *  select_directors
 */
bool select_directors(sqlite3 *db,  int cnt_movie, int movie_id )
{
    // printf("\n directors \n");

    sqlite3_stmt *stmt;
    int rc; //result codes

char sql[BUFSIZE];
char name[BUFSIZE];

snprintf(sql, BUFSIZE-1, "SELECT  movieid, personid  FROM directors where movieid=%d", movie_id);
 // printf("%s \n", sql);


// generate prepared statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }


int movieid;
int personid;

int cnt_director = 0;

// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        movieid = sqlite3_column_int(stmt, 0);
        personid = sqlite3_column_int(stmt, 1);
        // printf("movieid: %d \n", movieid);
        // printf("personid: %d \n", personid);
        // printf("person: %s \n", persons[personid] );
        // printf("\n");

        strcpy(name, persons[personid] );
      strcpy( movies[cnt_movie].directors[cnt_director],  name);

        rc = sqlite3_step(stmt);
        cnt_director++;
    } // while

    movies[cnt_movie].num_director = cnt_director;

// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}


/**
 *  select_writers
 */
bool select_writers(sqlite3 *db,  int cnt_movie, int movie_id )
{
    // printf("\n writers \n");

    sqlite3_stmt *stmt;
    int rc; //result codes

char sql[BUFSIZE];
char name[BUFSIZE];

snprintf(sql, BUFSIZE-1, "SELECT  movieid, personid  FROM writers where movieid=%d", movie_id);
 // printf("%s \n", sql);


// generate prepared statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }


int movieid;
int personid;

int cnt_writer = 0;

// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        movieid = sqlite3_column_int(stmt, 0);
        personid = sqlite3_column_int(stmt, 1);
        // printf("movieid: %d \n", movieid);
        // printf("personid: %d \n", personid);
        //printf("person: %s \n", persons[personid] );
        //printf("\n");

        strcpy(name, persons[personid] );
      strcpy( movies[cnt_movie].writers[cnt_writer],  name);

        rc = sqlite3_step(stmt);
        cnt_writer++;
    } // while

movies[cnt_movie].num_writer = cnt_writer;

// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}



/**
 *  select_casting
 */
bool select_casting(sqlite3 *db, int cnt_movie, int movie_id )
{
    // printf("\n casting \n");

    sqlite3_stmt *stmt;
    int rc; //result codes

char sql[BUFSIZE];
char role[BUFSIZE];
char star[BUFSIZE];


snprintf(sql, BUFSIZE-1, "SELECT  movieid, personid, role  FROM casting where movieid=%d", movie_id);
// printf("%s \n", sql);

// generate prepared statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }


int movieid;
int personid;

int cnt_cast = 0;

// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        movieid = sqlite3_column_int(stmt, 0);
        personid = sqlite3_column_int(stmt, 1);
        strcpy( role, (char *)sqlite3_column_text(stmt, 2) );
        //printf("movieid: %d \n", movieid);
        //printf("personid: %d \n", personid);
        //printf("person: %s \n", persons[personid] );
        //printf("role: %s \n", role);
        //printf("\n");

        strcpy(star,  persons[personid]);
        strcpy( movies[cnt_movie].cast[cnt_cast].star,  star);
        strcpy( movies[cnt_movie].cast[cnt_cast].role,  role);

        rc = sqlite3_step(stmt);
        cnt_cast++;
    } // while

    movies[cnt_movie].num_cast = cnt_cast;

// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}


/**
 *  select_movies
 */
bool select_movies(sqlite3 *db )
{
    sqlite3_stmt *stmt;
    int rc; //result codes

// generate prepared statement
    rc = sqlite3_prepare_v2(db,"SELECT  rowid, title, year, length FROM movies", -1, &stmt, 0);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc, sqlite3_errmsg(db));        return false;
    }
    
char title[BUFSIZE];

int rowid;
int year;
int length;
int cnt_movie = 0;

// read the line.
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW){
        rowid = sqlite3_column_int(stmt, 0);
        strcpy( title, (char *)sqlite3_column_text(stmt, 1) );
        year = sqlite3_column_int(stmt, 2);
        length = sqlite3_column_int(stmt, 3);
        // printf("rowid: %d \n", rowid);
        // printf("title: %s \n", title);
        // printf("year: %d \n", year);
        // printf("length: %d \n", length);
        // printf("\n");

        movies[cnt_movie].year = year;
       movies[cnt_movie]. length =  length;
        strcpy( movies[cnt_movie].title, title);

        select_casting(db, cnt_movie, rowid);
        select_directors(db,  cnt_movie, rowid);
        select_writers(db,  cnt_movie, rowid);

        rc = sqlite3_step(stmt);
        cnt_movie++;
    } // while

        num_movie = cnt_movie;
// release prepared statement
    rc = sqlite3_finalize(stmt);
    if(rc != SQLITE_OK){
        printf("ERROR(%d) %s\n",rc,sqlite3_errmsg(db));
    }

    return true;
}


/**
 * get_movies
 */
bool get_movies(char *filepath)
{ 
    sqlite3 *db;
   int rc; //result codes

    rc = sqlite3_open(filepath, &db);
    if(rc != SQLITE_OK){
        printf("cannot open: %s \n", filepath);
        return false;
    }

    select_persons(db);
    select_movies(db);
    sqlite3_close(db);

    return true;
}


/**
 * dump
 */
void dump(struct movie m)
{
    printf("\n");

    // printf("id: %d \n", m.id);
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
int main(void)
{
    char* FILEPATH = "movies.db";

get_movies(FILEPATH);

 for(int i=0; i<num_movie; i++)
    {
        dump(movies[i]);
    }

    return EXIT_SUCCESS;
 }


// title: The Matrix 
// year: 1999 
// length: 196 
// cast: 
// star: Keanu Reeves 
// role: Neo 


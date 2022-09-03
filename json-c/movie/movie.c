/**
 * movies.c
 * 2022-06-01 K.OHWADA
 */

// Deserializing data from movie JSON 
// reference : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_76/main.cpp

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <json.h>
 #include <assert.h>
#include "movies.h"

 const int NUM_MOVIES = 10;
struct movie movies[NUM_MOVIES];


/**
 * parse_writers
 */
void parse_writers(int cnt_movie, json_object* array_obj)
{
if (json_object_get_type(array_obj) == json_type_array) {
    int array_num = json_object_array_length(array_obj);
    json_object* obj;
    // printf("writers: \n");
    movies[cnt_movie].num_writer = array_num;
    for (int i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(array_obj, i);
            if (json_object_get_type(obj) == json_type_string) {
                char* name = (char *)json_object_get_string(obj);
                strcpy( movies[ cnt_movie].writers[i], name);
                // printf("%d: %s\n", i, name);
            }
    } // for
    } //if
}


/**
 * parse_directors
 */
void parse_directors(int cnt_movie, json_object* array_obj)
{
if (json_object_get_type(array_obj) == json_type_array) {
    int array_num = json_object_array_length(array_obj);
    json_object* obj;
    // printf("directors: \n");
    movies[cnt_movie].num_director = array_num;
    for (int i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(array_obj, i);
            if (json_object_get_type(obj) == json_type_string) {
                char* name = (char *)json_object_get_string(obj);
                strcpy( movies[ cnt_movie].directors[i], name);
                // printf("%d: %s\n", i, name);
            }
    } // for
} //if
}


/**
 * parse_cast
 */
void  parse_cast(int cnt_movie, int i, json_object* cast_obj)
{
    json_object_object_foreach(cast_obj, key, val) {
        if (strcmp(key, "name") == 0) { 
                char* name = (char*)json_object_get_string(val);
                strcpy( movies[cnt_movie].cast[i].role,  name);
                // printf("name: %s \n",  name );
        } else if (strcmp(key, "star") == 0) { 
                char* star = (char*)json_object_get_string(val);
                strcpy( movies[cnt_movie].cast[i].star,  star);
                // printf("star: %s \n", star );
        }
    } // foeeach
}


/**
 * parse_cast_array
 */
void  parse_cast_array(int cnt_movie, json_object* array_obj)
{
if (json_object_get_type(array_obj) == json_type_array) {
    int array_num = json_object_array_length(array_obj);
    json_object* obj;
    movies[cnt_movie].num_cast = array_num;
    for (int i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(array_obj, i);
            parse_cast(cnt_movie, i, obj);
    } // for
    } //if
}


/**
 * parse_movie
 */
void parse_movie(int i, json_object* movie_obj)
{
    json_object_object_foreach(movie_obj, key, val) {
            if (strcmp(key, "id") == 0) { 
                int id = json_object_get_int(val);
                movies[i].id = id;
                // printf("id: %d \n", id );
            } else if (strcmp(key, "length") == 0) { 
                int length = json_object_get_int(val);
                movies[i].length = length;
                // printf("length: %d \n", length );
            } else if (strcmp(key, "title") == 0) { 
                char* title = (char *)json_object_get_string(val);
                strcpy( movies[i].title, title);
                // printf("title: %s \n", title );
            } else if (strcmp(key, "year") == 0) { 
                int year = json_object_get_int(val);
                movies[i].year = year;
                // printf("year: %d \n", year );
            } else if (strcmp(key, "cast") == 0) { 
                // printf("cast: \n");
                parse_cast_array(i, val);
            } else if (strcmp(key, "directors") == 0) { 
                parse_directors(i, val);
            } else if (strcmp(key, "writers") == 0) { 
                parse_writers(i, val);
              }
    } // foreach

}


/**
 * parse_movies
 */
void parse_movies(json_object* root_obj, int *num_movie)
{
    json_object *movies_obj;

    movies_obj = json_object_object_get(root_obj, "movies");
    // printf("columns_obj=%s\n", json_object_to_json_string(columns_obj));
    if (json_object_get_type(movies_obj) == json_type_array) {
        int array_num = json_object_array_length(movies_obj);
        *num_movie = array_num;
        json_object* obj;
        for (int i = 0; i < array_num; i++) {
            obj = json_object_array_get_idx(movies_obj, i);
            parse_movie(i, obj);
    } // for
    } // if
}


/**
 * deserialize
 */
bool deserialize(char *filepath, int *num_movie)
{
    json_object *root_obj;

     root_obj = json_object_from_file(filepath);
    if (!root_obj) {
        fprintf(stderr, "json parse error.\n");
        return false;
    }

    parse_movies(root_obj, num_movie);

    return true;
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
int main()
{
    char* FILEPATH = "movies.json";

    int num_movie;
    bool ret =deserialize(FILEPATH, &num_movie);
    if(!ret){
        return EXIT_FAILURE;
    }

   assert(num_movie == 2);
   assert( strcmp(movies[0].title, "The Matrix") == 0);
   assert( strcmp(movies[1].title, "Forrest Gump") == 0);

    for(int i=0; i<num_movie; i++){
        dump(movies[i]);
    }

    return EXIT_SUCCESS;
}


// id: 11001 
// title: The Matrix 
// year: 1999 
// length: 196 
// cast: 
// star: Keanu Reeves 
// role: Neo 


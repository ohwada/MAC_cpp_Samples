#pragma once
/**
 * http_file_server.h
 * 2022-06-01 K.OHWADA
 */

// return response file content


#include <stdlib.h>
#include <string.h>
#include "http_server.h"
 #include "response_builder.h"
#include "file_util.h"
#include "file_timestamp.h"
#include "mime.h"


// prototype
void get_file(char* path, char* file);
bool save_response_text(char* data, char* error);
bool save_response_binary(char* data, size_t size, char* error);
void get_save_filepath( char* path );



/**
 * get_file
 */
void get_file(char* path, char* file)
{
    const char SLASH = '/';
    const char STR_SLASH[] = "/";
    const char ROOT[] = "www";
    const char INDEX[] = "index.html";

    if( strcmp(path, STR_SLASH) == 0 ) {
        make_path( (char *)ROOT, (char *)INDEX, file);
    } else  if( path[0] == SLASH ) {
        make_path( (char *)ROOT, &path[1], file);
    }

}


/**
 *  save_response_text
 */
bool save_response_text(char* data, char* error)
{
    const size_t BUFSIZE = 512;
    char path[BUFSIZE];

    get_save_filepath( (char *)path );

    printf("save: %s \n", path);

    return file_text_write( (char* )path, data, error);
}


/**
 *  save_response_binary
 */
bool save_response_binary(char* data, size_t size, char* error)
{
    const size_t BUFSIZE = 512;
  char path[BUFSIZE];

    get_save_filepath( (char *)path );

    printf("save: %s \n", path);

    return file_binary_write( (char *)path,  (char *)data, size, error);
}


/**
 *  get_save_filepath
 */
void get_save_filepath( char* path )
{
    const size_t BUFSIZE = 512;
    char file[BUFSIZE];

    char* dir = "log"; 
    char* prefix = "response";
    char* ext = "txt";

    get_timestamp_filename(prefix, ext, file);

    make_path(dir, (char *)file, path);
}

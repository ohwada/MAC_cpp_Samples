#pragma once
/**
 * save.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file_util.h"
#include "file_timestamp.h"

// prototype
bool save_response( char*  response,  bool is_verbose );
bool save_body( char*  body, bool is_verbose );
void get_save_response_path(char* path);
void get_save_body_path(char* path);
void build_timestamp_file_path( char* dir, char* prefix, char* ext,char* path);


/**
 * save_response
 */
bool save_response( char*  response,  bool is_verbose )
{
    const size_t BUFSIZE = 512;
    char path[BUFSIZE];
     char error[BUFSIZE];

    get_save_response_path( (char *)path );

    bool ret = file_text_write( path, response, (char *)error );
    if(ret){
        if( is_verbose ) {
            printf("saved: %s \n", path);
        }
    } else {
        if( is_verbose ) {
            printf("write failed: %s %s \n", path, error);
        }
    }

    return ret;
}


/**
 * save_body
 */
bool save_body( char*  body,  bool is_verbose )
{
    const size_t BUFSIZE = 512;
    char path[BUFSIZE];
     char error[BUFSIZE];

    get_save_body_path( (char *)path );

    bool ret = file_text_write( path, body, (char *)error );
    if(ret){
        if( is_verbose ) {
            printf("saved: %s \n", path);
        }
    } else {
        if( is_verbose ) {
            printf("write failed: %s %s \n", path, error);
        }
    }

    return ret;
}


/**
 * get_save_response_path
 */
void get_save_response_path(char* path)
{
    char*  dir= "log";
    char*  prefix = "response";
    char*  ext = "txt";

    build_timestamp_file_path( dir, prefix, ext, path);

}


/**
 * get_save_body_path
 */
void get_save_body_path(char* path)
{
    char*  dir= "log";
    char*  prefix = "body";
    char*  ext = "txt";

    build_timestamp_file_path( dir, prefix, ext, path);

}


/**
 *  build_timestamp_file_path
 */
void build_timestamp_file_path( char* dir, char* prefix, char* ext,char* path)
{

    const size_t BUFSIZE = 512;
    char file[BUFSIZE];

     get_timestamp_filename(prefix, ext, (char *)file);

    make_path(dir, (char *)file, path);

}



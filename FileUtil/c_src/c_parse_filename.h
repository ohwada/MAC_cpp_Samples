#pragma once
/**
 * C Sample
 * 2020-02-01 K.OHWADA
 */

// parse file path

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


char* get_filename_with_ext(char *fullpath);

char* get_filename_without_ext(char *fullpath);

char* get_file_ext(char *fullpath);


/**
 * get_filename_with_ext
 */
char* get_filename_with_ext(char *fullpath) 
{

    const char SLASH = '/';


    int len = strlen(fullpath);
    char buf[len+1];

    strcpy(buf, fullpath);

    char *basename = strrchr(buf, SLASH);
    if(!basename) {
        printf("not find slash \n");
        return fullpath;
    }


    // omit the first SLASH
    char *basename1 = &basename[1];

    return basename1;
}



/**
 * get_filename_without_ext
 */
char* get_filename_without_ext(char *fullpath) 
{

    const char* STR_DOT = ".";

    char *basename = get_filename_with_ext(fullpath); 

    if(!basename) {
        return fullpath;
    }

    int len = strlen(basename);
    char buf[len+1];
    strcpy(buf, basename);

  char *fname = strtok(buf, STR_DOT);

    if(!fname) {
        printf("not find dot \n");
        return basename;
    }

  return fname;

}


/**
 * get_file_ext
 */
char* get_file_ext(char *fullpath) 
{

    const char DOT = '.';

    char *basename = get_filename_with_ext(fullpath); 

    if(!basename) {
        return "";
    }

    int len = strlen(fullpath);
    char buf[len+1];
    strcpy(buf, fullpath);

    char *ext = strrchr(buf, DOT);
    if(!ext) {
        printf("not find dot \n");
        return "";
    }


    // omit the first DOT
    char *ext1 = &ext[1];

    return ext1;

}


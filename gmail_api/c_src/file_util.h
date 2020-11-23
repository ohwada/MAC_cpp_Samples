#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// file utility

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> 
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


// prototype
bool existsFile (char* path);
bool writeTextFile(char* file, char* data, char *error);
char* readTextFile(char *file, char *error);



/**
 * existsFile
 */
bool existsFile (char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}



/**
 * writeTextFile
 */
bool writeTextFile(char* file, char* data, char *error)
{

    FILE *fp;
    int saved_errno;
    int res;

    fp = fopen(file, "w");
    if(!fp) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return false;
    }

    int ret = fputs( data , fp );
    if( ret == EOF ) {
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        res = false;
    } else {
        res = true;
    }

    fclose(fp);
    return res;
}


/**
 * readTextFile
 */
char* readTextFile(char *file, char *error)
{

    const char CHAR_NULL =  '\0';

   FILE *fp;
    int saved_errno;

    fp = fopen(file, "r");
    if(!fp){
        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
     
    int string_size = ftell(fp);

    rewind(fp);

    char* buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

    int read_size = fread(buffer, sizeof(char), string_size, fp);

    // null end for char string
    buffer[string_size] =  CHAR_NULL ;

    if (string_size != read_size){
    
           free(buffer);
           buffer = NULL;

        saved_errno = errno;
        strcpy( error, strerror(saved_errno) );
    }

    fclose(fp);

    return buffer;
}


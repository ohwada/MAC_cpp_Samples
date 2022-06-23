#pragma once
/**
 * file_util.h
 * 2022-05-01 K.OHWADA
 */


#include <stdbool.h>
#include <sys/stat.h>


// prototype
bool existsFile(char* path);


/**
 * existsFile
 */
bool existsFile(char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}

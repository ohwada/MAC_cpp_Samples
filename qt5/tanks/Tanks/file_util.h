#pragma once
/**
 * file_util.h
 * 2020-03-01 K.OHWADA
 */


#include <string>
#include <sys/stat.h>


// prototype
bool existsFile(std::string file);
int file_exists (char *filename) ;

/**
 * existsFile
 */
bool existsFile(std::string file)
{
    int ret = file_exists( (char *)file.c_str() );
    bool res = (ret == 0)?true:false;
    return res;
}


/**
 * file_exists
 * @ return 0 : exists, 1 : stat failed
 */
int file_exists (char *filename) 
{
  struct stat buffer;   
  return stat(filename, &buffer);
}

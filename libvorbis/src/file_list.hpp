#pragma once
/**
 * file_list.hpp
 * 2020-03-01 K.OHWADA
 */

// read filenames with spcified extension in directory
// using C++11

// reference : https://linuxjm.osdn.jp/html/LDP_man-pages/man3/readdir.3.html


#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

const int RET__SUCCESS = 0;
const int RET__ERR_EXISTS = 1;
const int RET__ERR_DIR = 2;
const int RET__ERR_OPEN = 3;

// porototype
int getFileListExt(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &err );
int getFileListExt2(std::string str_path, std::string ext1, std::string ext2, std::vector<std::string> &vec );
int getFileList(std::string str_path, std::vector<std::string> &vec, std::string &err );
bool existsFile(std::string path); 
bool file_exists (char* path);
bool isDir(std::string path);
bool is_dir(char* path);
bool isFile(std::string path);
bool is_file(char* path);
bool match_ext(std::string str, std::string ext);
void printFileList(  std::vector<std::string> vec);
void printError(int ret, std::string path, std::string err);
std::string makePath(std::string dir, std::string file);
bool makeDir(std::string dir, int mode);

/**
 * getFileListExt
 */
int getFileListExt(std::string str_path, std::string ext, std::vector<std::string> &vec1, std::string &err1)
{

    std::vector<std::string> vec2;
    std::string err2;
    int ret = getFileList(str_path, vec2, err2 );
    if( ret != RET__SUCCESS) {
        err1 = err2;
        return ret;
    }

for(std::string file: vec2) 
{
        bool ret = false;
        if( ext.length() > 0 ) {
            ret = match_ext(file, ext);
        } else {
            ret = true;
        }
        if(ret) {
            vec1.push_back( file );
        }
    } // for

    return RET__SUCCESS;
}


/**
 * getFileListExt2
 */
int getFileListExt2(std::string str_path, std::string ext1, 
std::string ext2, std::vector<std::string> &vec1, std::string &err1)
{

    std::vector<std::string> vec2;
    std::string err2;
    int ret = getFileList(str_path, vec2, err2 );
    if( ret != RET__SUCCESS) {
        err1 = err2;
        return ret;
    }

bool is_ext1 =(ext1.length() > 0) ? true : false;
bool is_ext2 =(ext2.length() > 0) ? true : false;

for(std::string file: vec2) 
{
        bool ret = false;
        if( is_ext1 && is_ext2 ) {
            bool ret1 = match_ext(file, ext1);
            bool ret2 = match_ext(file, ext2);
            ret = ret1|| ret2;
       } else if( is_ext1 ) {
            ret = match_ext(file, ext1);
       } else if( is_ext2 ) {
            ret = match_ext(file, ext2);
        } else {
            ret = true;
        }
        if(ret) {
            vec1.push_back( file );
        }
    } // for

    return RET__SUCCESS;
}


/**
 * getFileList
 */
int getFileList(std::string str_path, std::vector<std::string> &vec,  std::string &error)
{

    char* path = (char *)str_path.c_str();

    bool ret1 = file_exists(path);
    if( !ret1 ) {
        return RET__ERR_EXISTS;
    }

    bool ret2 = is_dir(path);
    if ( !ret2 ) {
        return RET__ERR_DIR;
    }


    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        error = strerror(errno);
        return RET__ERR_OPEN;
    }

    const std::string DOT = (char *)".";
    const std::string TWO_DOT = (char *)"..";
    struct dirent * ent;

    while ((ent = readdir (dir)) != NULL) {
        std::string file = std::string( ent->d_name );
        if (( file == DOT  )||( file == TWO_DOT )){
            continue;
        }

        vec.push_back( std::string( ent->d_name ) );
    } // while

    closedir (dir);

    return RET__SUCCESS;
}


/**
 * existsFile
 */
bool existsFile(std::string path) 
{
    return file_exists(  (char *)path.c_str() ); 
}


/**
 * file_exists
 */
bool file_exists(char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
}


 /**
 * isDir
 */
bool isDir(std::string path)
{
    return is_dir( (char *)path.c_str() );
}


/**
 * is_dir
 */
bool is_dir(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return false;
    }

    mode_t m = sb.st_mode;
    bool res = ( S_ISDIR(m) )? true: false;
    return res;        
}


/**
 * isFile
 */
bool isFile(std::string path)
{
    return is_file( (char*)path.c_str() );
}

/**
 * is_file
 */
bool is_file(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return false;
    }

    mode_t m = sb.st_mode;
    bool res = ( S_ISREG(m) )? true: false;
    return res;        
}

/**
 * match_ext
 */
bool match_ext(std::string str, std::string ext)
{
    const std::string DOT = (char *)".";
    std::string dot_ext = DOT + ext;
    int pos = str.rfind(dot_ext );
    bool ret = (pos == std::string::npos)? false: true;
    return ret;
}


/**
 * printFileList
 */
void printFileList(  std::vector<std::string> vec)
{
    for(int i=0; i<vec.size(); i++) {    
        std::cout << ( i + 1 ) << " : " << vec[i] << std::endl;
    }
}


/**
 * printError
 */
void printError(int ret, std::string path, std::string err)
{
  if(ret == RET__ERR_EXISTS ) {
        std::cerr << "NOT found: " << path << std::endl;
    } else if(ret == RET__ERR_DIR ) {
        std::cerr << "NOT directory: " << path << std::endl;
    } else if(ret == RET__ERR_OPEN ) {
        std::cerr << "NOT open: " << path << std::endl;
        std::cerr << err << std::endl;
    }
}


/**
 * makePath
 */
std::string makePath(std::string dir, std::string file)
{
    const char SLASH = '/';
    int len = dir.size();
    char ch = dir.at(len-1);
    if ( ch != SLASH){
        dir.push_back(SLASH);
    }
    std::string path = dir + file;
return path;
}


/**
 * makeDir
 */
bool makeDir(std::string dir, int mode)
{
    int ret1 = mkdir( (char *)dir.c_str(), mode);
    bool ret2 = (ret1 == 0)? true: false;
    return ret2;
}
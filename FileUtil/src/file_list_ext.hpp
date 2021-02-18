/**
 * C++ Sample
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


// porototype
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error );
bool file_exists (char* path);
bool is_dir(char* path);
bool match_ext(std::string str, std::string ext);
void printFileList(  std::vector<std::string> vec);


/**
 * getFileList
 */
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error)
{

    char* path = (char *)str_path.c_str();

    bool ret1 = file_exists(path);
    if( !ret1 ) {
        error = std::string("not found: ") + path;
        return false;
    }

    bool ret2 = is_dir(path);
    if ( !ret2 ) {
        error = std::string("not directory: ") + path;
        return false;
    }


    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        error = strerror(errno) + std::string(" : ") +path;
        return false;
    }

    const std::string DOT = (char *)".";
    const std::string TWO_DOT = (char *)"..";
    struct dirent * ent;

    while ((ent = readdir (dir)) != NULL) {
        std::string file = std::string( ent->d_name );
        if (( file == DOT  )||( file == TWO_DOT )){
            continue;
        }
        bool ret = match_ext(file, ext);
        if(ret) {
            vec.push_back( std::string( ent->d_name ) );
        }
    } // while

    closedir (dir);

    return true;
}


/**
 * file_exists
 */
bool file_exists (char *path) 
{
    struct stat   sb;   
    int ret = stat(path, &sb);
    bool res = ( ret == 0 )? true: false;
    return res;
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
 * match_ext
 */
bool match_ext(std::string str, std::string ext)
{
    const std::string DOT = (char *)".";
    std::string dot_ext = DOT + ext;
    int pos = str.rfind(dot_ext );
    bool ret = (pos == std::string::npos)?false:true;
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
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
int is_dir(char* path);
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error);
bool match_ext(std::string str, std::string ext);


/**
 * is_dir
 * @return 1 : is_dir -1 : not found
 */
int is_dir(char* path)
{
    struct stat sb;
    int ret = stat(path, &sb);
    if(ret != 0){
        return -1;
    }

    mode_t m = sb.st_mode;
    int res = ( S_ISDIR(m) )?1:0;
    return res;        
}


/**
 * getFileList
 */
bool getFileList(std::string str_path, std::string ext, std::vector<std::string> &vec, std::string &error)
{

    char* path = (char *)str_path.c_str();

    int ret = is_dir(path);
    if(ret == -1) {
        error = std::string("not found: ") + path;
        return false;
    } else if (ret == 0) {
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


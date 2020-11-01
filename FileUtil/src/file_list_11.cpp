/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// read filenames in directory using C++11

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
bool getFileList(std::string str_path, std::vector<std::string> &vec);


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
bool getFileList(std::string str_path, std::vector<std::string> &vec)
{

    char* path = (char *)str_path.c_str();

    int ret = is_dir(path);
    if(ret == -1) {
        std::cout << "not found: " << path << std::endl;
        return false;
    } else if (ret == 0) {
        std::cout << "not directory: " << path << std::endl;
        return false;
    }

    DIR *dir;
    dir = opendir (path);
    if (!dir) {
        printf ("%s : %s \n", strerror(errno), path);
        return false;
    }

    struct dirent * ent;
    while ((ent = readdir (dir)) != NULL) {
        vec.push_back( std::string( ent->d_name ) );
    } 

    closedir (dir);

    return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{

// current directory
    std::string path = ".";

    if(argc == 2) {
        path = argv[1];
    }else {
        std::cout <<  "Usage: " << argv[0] << " [directory path] " << std::endl;
    }

    std::vector<std::string> vec;
    getFileList(path, vec);

    for(int i=0; i<vec.size(); i++) {    
        std::cout << vec[i] << std::endl;
    }

	return EXIT_SUCCESS;
}


/**
 * save.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "file_util.hpp"

// prototype
bool save_body( std::string body, bool is_verbose);
std::string build_timestamp_file_path(  std::string dir,  std::string prefix, std::string ext);


/**
 * save_body
 */
bool save_body( std::string body,   bool is_verbose )
{
    std::string dir("log");
    std::string prefix("body");
    std::string ext("html");

    std::string path =  build_timestamp_file_path(dir, prefix, ext);

    bool ret = writeTextFile( path, body);
    if(ret){
        if( is_verbose ) {
            std::cout << "saved: " << path << std::endl;
        }
    } else {
        if( is_verbose ) {
            std::cerr << "cannot write: " << path << std::endl;
        }
    }

    return ret;
}


/**
 * build_timestamp_file_path
 */
std::string build_timestamp_file_path(  std::string dir,  std::string prefix, std::string ext)
{
    std::string filename;

    getTimestampFileName(prefix, ext, filename);

    return make_path(dir, filename);
}


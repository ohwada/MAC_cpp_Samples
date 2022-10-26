/**
 * save.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "file_util.hpp"

// prototype
bool save_reponse( std::string response,   bool is_verbose );
bool save_body( std::string body, bool is_verbose= false );
std::string get_save_response_path();
std::string get_save_body_path();
std::string build_timestamp_file_path(  std::string dir,  std::string prefix, std::string ext);


/**
 * save_response
 */
bool save_reponse( std::string response,   bool is_verbose )
{
    std::string path = get_save_response_path();

    bool ret = writeTextFile( path, response);
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
 * save_body
 */
bool save_body( std::string body,   bool is_verbose )
{
    std::string path = get_save_body_path();

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
 * get_save_response_path
 */
std::string get_save_response_path()
{
    std::string dir("log");
    std::string prefix("response");
    std::string ext("txt");

    return build_timestamp_file_path(dir, prefix, ext);
}


/**
 * get_save_body_path
 */
std::string get_save_body_path()
{
    std::string dir("log");
    std::string prefix("body");
    std::string ext("html");

    return build_timestamp_file_path(dir, prefix, ext);
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


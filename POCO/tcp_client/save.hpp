/**
 * save.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include "timestamp.hpp"
#include "file_stream.hpp"

// prototype
bool save_response( std::string response,   bool is_verbose );
bool save_body( std::string body, bool is_verbose= false );
std::string get_save_response_path();
std::string get_save_body_path();


/**
 * save_response
 */
bool save_response( std::string response,   bool is_verbose )
{
    std::string path = get_save_response_path();

    bool ret = file_text_write( path, response);
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

    bool ret = file_text_write( path, body);
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


/**
 * poco_client_save.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include "poco_timestamp.hpp"
#include "poco_file_stream.hpp"

// prototype
bool save_request( 
std::string request,   bool is_verbose=true );
bool save_response( 
std::string response,   bool is_verbose=true );
std::string get_save_response_path();


/**
 * save_request
 */
bool save_request( std::string request,   bool is_verbose )
{
    std::string path = get_save_response_path();

    bool ret = file_text_write( path, request);
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
 * save_response
 */
bool save_response( std::string response,   bool is_verbose )
{
    std::string dir("log");
    std::string prefix("request");
    std::string ext("txt");

    std::string path = build_timestamp_file_path(dir, prefix, ext);
 
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
 * get_save_response_path
 */
std::string get_save_response_path()
{
    std::string dir("log");
    std::string prefix("response");
    std::string ext("txt");

    return build_timestamp_file_path(dir, prefix, ext);
}


/**
 * apikey.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include "file_util.hpp"
#include "trim.hpp"
#include "home_directory.h"

// prototype
std::string  get_apikey();


/**
 *   get_apikey
 */
std::string  get_apikey()
{
    std::string home( getHomeDir() );
    
    auto dir = make_path(home, "google_api");
    auto filepath = make_path(dir, "vision_api_key.txt");
  
    std::cout << filepath << std::endl;

    std::string text;
    bool ret = readTextFile(filepath, text);
    if(!ret){
        return "";
    }

    return trim(text);
}



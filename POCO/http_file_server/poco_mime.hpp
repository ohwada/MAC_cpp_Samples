#pragma once
/**
 *  poco_mime.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "mime.hpp"

// prototype
std::string get_mime(Poco::File file);
std::string get_mime(Poco::Path path);


/**
 *  get_mime
 */
std::string get_mime(Poco::File file)
{
    std::string fpath = file.path();
    Poco::Path path(fpath);
    return get_mime(path); 
}


/**
 *  get_mime
 */
std::string get_mime(Poco::Path path)
{
    std::string ext = path.getExtension();
    return ext_to_mime(ext); 
}

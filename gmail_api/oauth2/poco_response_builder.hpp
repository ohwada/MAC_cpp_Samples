#pragma once
/**
 *  poco_response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/Format.h"

// prototype
std::string build_response(std::string code, std::string scope);


/**
 *  build_response
 */
std::string build_response(std::string code, std::string scope)
{
    std::string FORMAT=
R"(<html><head></head><body><h1>Local Server</h1><font size="+2">code<br/>|%s| <br/>scope<br/>|%s|<br/></font></body></html>)";

  std::string text;
    Poco::format(text, FORMAT,  code, scope);

    return text;
}

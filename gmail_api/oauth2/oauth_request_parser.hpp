#pragma once
/**
 *  oauth_request_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <regex>
#include "trim.hpp"

// prototype
bool parseRequestAuthCode(std::string request,  std::string &code, std::string &scope);


/**
 *  parse_request
 */
bool parseRequestAuthCode(std::string request,  std::string &code, std::string &scope)
{

    std::string str = R"(code=(.*)&scope=(.*)HTTP)";

    std::regex reg(str);


    std::smatch m;

  if (std::regex_search(request, m, reg)) 
{
    code = trim( m[1].str() );
    scope = trim( m[2].str() );
} else {
    return false;
}
    
    return true;
}

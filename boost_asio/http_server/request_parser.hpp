#pragma once
/**
 * request_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include<regex>

// prototype
bool parse_request(std::string request,  std::string &path);


/**
 *  parse_request
 */
bool parse_request(std::string request,  std::string &path)
{

    const std::string PATTEN = R"(GET (/.*) HTTP)";

    std::regex reg(PATTEN);

    std::smatch m;

    if (std::regex_search(request, m, reg)) 
    {
        path = m[1].str();
    } else {
        return false;
    }

    return true;
}


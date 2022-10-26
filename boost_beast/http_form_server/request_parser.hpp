#pragma once
/**
 * request_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include<regex>

// prototype
bool parse_request(std::string request, std::string &key, std::string &value);


/**
 *  parse_request
 */
bool parse_request(std::string request, std::string &key, std::string &value)
{

    std::string str = R"((\w+)=(\w+))";

    std::regex reg(str);

    std::smatch m;

    if (std::regex_search(request, m, reg)) 
    {
        key = m[1].str();
        value = m[2].str();
    } else {
        return false;
    }

    return true;
}


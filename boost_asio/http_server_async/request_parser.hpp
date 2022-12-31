#pragma once
/**
 * request_parser.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include<regex>
#include <boost/algorithm/string/trim.hpp>

// prototype
std::string parse_path(std::string request);


/**
 *  parse_path
 */
std::string parse_path(std::string text)
{
    const std::string PATTERN = R"(GET (/.*) HTTP)";

    std::regex re(PATTERN);

    std::smatch m;

    bool ret = std::regex_search(text, m, re);

    if(!ret){
        std::cerr << "unmatch" << std::endl;
        return "";
    }

    auto res = boost::algorithm::trim_copy( m[1].str() );

    return res;

}


#pragma once
/**
 * ws_request_parser.hpp
 * 2022-10-01 K.OHWADA
 */

#include <regex>
#include <boost/algorithm/string/trim.hpp>


// prototype
 std::string parse_seckey( std::string request );


/**
 *  parse_seckey
 */
std::string parse_seckey( std::string request )
{

    const std::string PATTERN = 
R"(Sec-WebSocket-Key:(.*)\r\n)";

    std::regex re(PATTERN);

    std::smatch m;

    bool ret = std::regex_search(request, m, re);

    if(!ret){
        std::cerr << "unmatch" << std::endl;
        return "";
    }

    auto res = boost::algorithm::trim_copy( m[1].str() );

    return res;
}



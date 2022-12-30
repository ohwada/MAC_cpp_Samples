#pragma once
/**
 * ws_response_parser.hpp
 * 2022-10-01 K.OHWADA
 */

#include <regex>
#include <boost/algorithm/string/trim.hpp>


// prototype
 std::string parse_status_code( std::string request );
 std::string parse_accept_key( std::string request );


/**
 *  parse_status_code
 */
std::string parse_status_code( std::string request )
{

    const std::string PATTERN = 
R"(HTTP/1.1 (\d+) (.*)\r\n)";

    std::regex re(PATTERN);

    std::smatch m;

    bool ret = std::regex_search(request, m, re);

    if(!ret){
        std::cerr << "unmatch" << std::endl;
        return "";
    }

    // std::cout << m[1].str() << std::endl;
    // std::cout << m[2].str() << std::endl;

    auto res = boost::algorithm::trim_copy( m[1].str() );

    return res;
}


/**
 *  parse_accept_key
 */
std::string parse_accept_key( std::string request )
{

    const std::string PATTERN = 
R"(Sec-WebSocket-Accept:(.*)\r\n)";

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


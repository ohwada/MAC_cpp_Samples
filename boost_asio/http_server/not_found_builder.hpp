#pragma once
/**
 * not_found_builder.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include <boost/format.hpp>
#include "response_builer.hpp"

// prototype
std::string build_msg_not_found(std::string path);
std::string get_response_header_not_found(std::string html);


/**
 *  build_msg_not_found
 */
std::string build_msg_not_found(std::string path)
{
    const std::string FORMAT = R"(
<h1>Not Found</h1>
<h2> %s </h2>
)";

    std::string msg =
    boost::str( boost::format(FORMAT) % path);

    return msg;
}


/**
 *  get_response_not_found
 */
std::string get_response_header_not_found(std::string html)
{
    const std::string HEADER_NOT_FOUND("HTTP/1.1 404  Not Found\r\n");

    std::string mime("text/html");

    std::string req = build_response_header_from_body_mime(html, mime);

    std::string header =
    HEADER_NOT_FOUND
    + req;

    return header;
}



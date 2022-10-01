/**
 * http_server.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include "file_util.hpp"


// prototype
bool get_index_html(std::string &text);
std::string build_response(std::string html);


/**
 * get_index_html
 */
bool get_index_html(std::string &text)
{
    std::string file("data/index.html");
    return readTextFile(file, text);
}


/**
 *  build_response
 */
std::string build_response(std::string html)
{

    const std::string CRLF("\r\n");

 const std::string HEADER_OK("HTTP/1.1 200 OK\r\n");
    const std::string HEADER_CONTENT_HTML("Content-Type: text/html\r\n");

    const std::string HEADER_CONTENT_LENGTH("Content-Length: ");

    const std::string CLOSE("Connection: Close\r\n");

    std::string content_length = 
    HEADER_CONTENT_LENGTH 
    +std::to_string( html.size() )
    + CRLF;

    std::string response = 
    HEADER_OK
    + HEADER_CONTENT_HTML
    +  content_length
    + CRLF
    + html;

    return response;
}



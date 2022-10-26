#pragma once
/**
 * response_builer.hpp
 */

#include <iostream>
#include <string>
#include <chrono>
#include <boost/format.hpp>


// prototype
std::string build_response_ok(std::string body, std::string mime);
std::string build_response_header_ok(std::string body, std::string mime);
std::string build_response_header_from_body_mime(std::string body, std::string mime);
std::string build_response_from_header_body(std::string header, std::string body);
std::string getDate();


/**
 * build_response_ok
 */
std::string build_response_ok(std::string body, std::string mime)
{
    std::string header = build_response_header_ok( body, mime);

    return build_response_from_header_body(header, body);
}


/**
 * build_response
 */
std::string build_response_from_header_body(std::string header, std::string body)
{
    const std::string CRLF("\r\n");

    std::string response = 
    header
    + CRLF
    + body;

    return response;
}


/**
 * build_response_header_ok
 */
std::string build_response_header_ok(std::string body, std::string mime)
{
    const std::string HEADER_OK("HTTP/1.1 200 OK\r\n");

    std::string req = build_response_header_from_body_mime(body, mime);

    std::string header =
    HEADER_OK
    + req;

    return header;
}


/**
 * build_response_header_from_body_mime
 */
std::string build_response_header_from_body_mime(std::string body, std::string mime)
{

  const std::string  FORMAT_CONTENT_TYPE("Content-Type: %s \r\n");

    const std::string  FORMAT_CONTENT_LENGTH("Content-Length: %d \r\n");

  const std::string FORMAT_DATE("Date: %s \r\n");

    const std::string CLOSE("Connection: Close\r\n");


    std::string header_content_type = 
    boost::str( boost::format(FORMAT_CONTENT_TYPE) % mime);

    std::string header_content_length = 
    boost::str( boost::format(FORMAT_CONTENT_LENGTH) % body.size());

 std::string header_date = 
    boost::str( boost::format(FORMAT_DATE) % getDate() );

    std::string response = 
    header_date
    + header_content_type
    +  header_content_length;

    return response;
}


/**
 *   getDate
 */
std::string getDate()
{
// RFC5322 format
// Sun, 06 Nov 1994 08:49:37 GMT

    const char FORMAT[] = "%a, %d %b %Y %H:%M:%S GMT";

    const size_t BUFSIZE = 128;
    char buf[BUFSIZE];

    std::time_t now = std::time(nullptr);

    std::tm *tm_now = gmtime(&now);

    std::strftime( ( char *)buf, BUFSIZE, (char *)FORMAT, tm_now);

    return std::string( buf );
}

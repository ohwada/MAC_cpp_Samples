#pragma once
/**
 * http_response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <boost/format.hpp>
#include "file_util.hpp"
#include "parse_filename.hpp"
#include "mime.hpp"


// prototype
std::string build_response_text(std::string text, std::string mime);
std::string build_response_file(std::string file);
std::string build_response_not_found(std::string path);
std::string build_response_header_ok(int length, std::string mime, bool is_crlf);
 std::string build_response_header_not_found(int length, std::string mime,  bool is_crlf);
std::string build_response_header(int length, std::string mime, bool is_crlf);
 std::string build_msg_not_found(std::string path);


/**
 * build_response_text
 */
std::string build_response_text(std::string text, std::string mime)
{
    std::string header = build_response_header_ok( text.length(), mime, true);

    std::string response = 
    header
    + text;

    return response;
}



/**
 * build_response_file
 */
std::string build_response_file(std::string file)
{

    auto ext = getFileNameExt(file);
    auto mime = get_mime(ext);

    std::cout << "ext: " << ext << std::endl;
    std::cout << "mime: " << mime << std::endl;

    std::string data;
    bool ret = readBinaryFile2(file, data);
    if(!ret){
        std::cerr << "cannot read: " << file << std::endl;
    }

    int length = data.size();

   std::cout << "length: " << length << std::endl;

    std::string header = build_response_header_ok(length, mime, true);

    std::string response = 
    header
    + data;

    return response;
}


/**
 *  build_response_not_found
 */
std::string build_response_not_found(std::string path)
{

    std::string mime("text/html");

    auto msg = build_msg_not_found(path);

    auto header = build_response_header_not_found( msg.size(), mime,  true);

    std::string response = 
    header + msg;

    return response;
}


/**
 * build_response_header_ok
 */
std::string build_response_header_ok(int length, std::string mime, bool is_crlf)
{

    const std::string HEADER_OK(
"HTTP/1.1 200 OK\r\n");

    auto header = build_response_header(length, mime, is_crlf);

    std::string res =
    HEADER_OK + header;

    return res;
}


/**
 *  build_response_header_not_found
 */
 std::string build_response_header_not_found(int length, std::string mime,  bool is_crlf)
{

    const std::string HEADER_NOT_FOUND(
"HTTP/1.1 404  Not Found\r\n");

    auto header = build_response_header(length, mime, is_crlf );

    std::string res = HEADER_NOT_FOUND + header;

    return res;
}



/**
 * build_response_header
 */
std::string build_response_header(int length, std::string mime, bool is_crlf)
{
    const std::string CRLF("\r\n");

    const std::string FORMAT_CONTENT_TYPE(
"Content-Type: %s \r\n");

    const std::string  FORMAT_CONTENT_LENGTH(
"Content-Length: %d \r\n");

    std::string header_content_type = 
    boost::str( boost::format(FORMAT_CONTENT_TYPE) % mime);
   
    std::string header_content_length = 
    boost::str( boost::format(FORMAT_CONTENT_LENGTH) % length );

    std::string header =
    header_content_type
    + header_content_length;
    if(is_crlf){
        header += CRLF;
    }

    return header;
}


/**
 *  build_msg_not_found
 */
 std::string build_msg_not_found(std::string path)
{

    const std::string FORMAT(
"<html><head></head><body><h1>Not Found</h1><h2> %s </h2></body></html>");

     std::string msg = 
    boost::str( boost::format(FORMAT) % path );

    return msg;
}



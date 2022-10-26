#pragma once
/**
 * http_file_server.hpp
 * 2022-06-01 K.OHWADA
 */

// return response file content

#include <iostream>
#include <string>
#include "file_util.hpp"
#include "parse_filename.hpp"

// prototype
std::string read_file(std::string file);
std::string get_mime(std::string path);
bool is_text(std::string path);
bool iequals(std::string ext1, std::string ext2);
std::string build_response(std::string header, std::string body);


/**
 * get_file
 */
std::string get_file(std::string path)
{
    const char SLASH = '/';
    const std::string STR_SLASH("/");
    const std::string ROOT("www");
    const std::string INDEX("/index.html");

    std::string file;
    if(path == STR_SLASH ){
        file= ROOT +  INDEX;
    } else  if( path[0] == SLASH ) {
       file = ROOT  + path;
    }
    return file;
}

/**
 * read_file
 */
std::string read_file(std::string file)
{
    if( is_text(file) ){
        std::string text;
        bool ret1 = readTextFile(file, text);
        if(ret1) {
            return text;
        }
    } else {
        std::string data;
        bool ret2 = readBinaryFile2(file, data);
        if(ret2) {
            return data;
        }
    }

    return NULL;
}


/**
 *  get_mime
 */
std::string get_mime(std::string path)
{
    std::string ext = getFileNameExt(path);

    if(iequals(ext, "htm"))  return "text/html";
    if(iequals(ext, "html")) return "text/html";
    if(iequals(ext, "php"))  return "text/html";
    if(iequals(ext, "css"))  return "text/css";
    if(iequals(ext, "txt"))  return "text/plain";
    if(iequals(ext, "js"))   return "application/javascript";
    if(iequals(ext, "json")) return "application/json";
    if(iequals(ext, "xml"))  return "application/xml";
    if(iequals(ext, "swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, "flv"))  return "video/x-flv";
    if(iequals(ext, "png"))  return "image/png";
    if(iequals(ext, "jpe"))  return "image/jpeg";
    if(iequals(ext, "jpeg")) return "image/jpeg";
    if(iequals(ext, "jpg"))  return "image/jpeg";
    if(iequals(ext, "gif"))  return "image/gif";
    if(iequals(ext, "bmp"))  return "image/bmp";
    if(iequals(ext, "ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, "tiff")) return "image/tiff";
    if(iequals(ext, "tif"))  return "image/tiff";
    if(iequals(ext, "svg"))  return "image/svg+xml";
    if(iequals(ext, "svgz")) return "image/svg+xml";
    return "application/text";
}


/**
 *  is_text
 *
 */
bool is_text(std::string path)
{
    std::string ext = getFileNameExt(path);

    if(iequals(ext, "htm"))  return true;
    if(iequals(ext, "html")) return true;
    if(iequals(ext, "txt"))  return true;
    return false;
}


/**
 *  iequals
 */
bool iequals(std::string ext1, std::string ext2)
{
    bool ret = (ext1 == ext2)? true: false;
    return ret;
}


std::string build_response(std::string header, std::string body)
{
    const std::string CRLF("\r\n");

    std::string response =
    header
    + CRLF
    + body;

    return response;
}


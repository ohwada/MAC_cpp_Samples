#pragma once
/**
 * mime.h
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <string.h>


// prototype
char* get_mime(char* ext);
bool is_text_file(char* ext);
bool iequals(char* ext1, char* ext2);


/**
 *  get_mime
 */
char* get_mime(char* ext)
{
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
 *  is_text_file
 *
 */
bool is_text_file(char* ext)
{
    if(iequals(ext, "htm"))  return true;
    if(iequals(ext, "html")) return true;
    if(iequals(ext, "txt"))  return true;
    return false;
}


/**
 *  iequals
 */
bool iequals(char* ext1, char* ext2)
{
    bool ret = (strcmp(ext1, ext2) == 0)? true: false;
    return ret;
}


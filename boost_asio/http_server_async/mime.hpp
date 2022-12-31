#pragma once
/**
 * mime.hpp
 * 2022-06-01 K.OHWADA
 */


// prototype
std::string get_mime(std::string ext);
bool iequals(std::string ext1, std::string ext2);


/**
 *  get_mime
 */
std::string get_mime(std::string ext)
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
 *  iequals
 */
bool iequals(std::string ext1, std::string ext2)
{
    bool ret = (ext1 == ext2)? true: false;
    return ret;
}


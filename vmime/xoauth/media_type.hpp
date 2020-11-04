#pragma once
/**
  * vmime sample
 * 2020-07-01 K.OHWADA
 */

// content type

#include <string>


// prototype
void getMediaType(std::string ext, std::string &type);


/**
 * getMediaType
 */
void getMediaType(std::string ext, std::string &type)
{
    const std::string MEDIA_TYPE_TXT("text/plain");
    const std::string MEDIA_TYPE_PNG("image/png");
    const std::string MEDIA_TYPE_JPG("image/jpg");
    const std::string MEDIA_TYPE_OCTET_STREAM(
    "application/octet-stream");

    if (ext == "txt"){
        type = MEDIA_TYPE_TXT;
    } else if (ext == "png"){
        type = MEDIA_TYPE_PNG;
    } else if (ext == "jpg"){
        type = MEDIA_TYPE_JPG;
    } else {
        type = MEDIA_TYPE_OCTET_STREAM;
    }

}


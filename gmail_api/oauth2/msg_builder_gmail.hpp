#pragma once
/**
 * msg_builder_gmail.hpp
 * 2022-06-01 K.OHWADA
 */

// build send message for Gmail API


#include "msg_builder.hpp"
#include "base64url.hpp"


// prototype
std::string buildRequestMailSendJson(std::string msg);
bool saveRequestJson(std::string msg);


/**
 * buildRequestMailSendJson
 * base64url encoding
 */
std::string buildRequestMailSendJson(std::string msg)
{
const std::string FORMAT = R"({ "raw": "%s" })"; 

// over 1MB when image
    std::string b64 = base64url_encode(msg);

    std::string request;
    Poco::format(request, FORMAT, b64 );

    return request;
}

/**
 * saveRequestJson
 */
bool saveRequestJson(std::string msg)
{

    std::string dir("log");
    std::string prefix("request");
    std::string ext("json"); 
    
    std::string path=  build_timestamp_file_path(dir, prefix, ext);

    return  file_text_write(path,  msg );
}

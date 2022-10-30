#pragma once
/**
 * gmail_api_request_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "Poco/Format.h"


// prototype
std::string build_api_msg_request( std::string url_api, std::string id );


/**
 * build_api_msg_request
 */
std::string build_api_msg_request( std::string url_api, std::string id )
{
    const std::string FORMAT("%s/%s");

    std::string url;
Poco::format(url, FORMAT, url_api, id);

    return url;
}


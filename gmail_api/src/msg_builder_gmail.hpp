#pragma once
/**
 * Gmal API sample
 * 2020-07-01 K.OHWADA
 */

// build send message


#include "msg_builder_gmail.h"
#include "msg_builder.hpp"
#include "base64url.hpp"


// prototype
void buildDefaultBody( std::string &ret_body);
void buildSendRequestJson(std::string msg, std::string &request);


/**
 * 
 */
void buildDefaultBody( std::string &ret_body)
{

    char body[BODY_SIZE];
    buildDefaultBody( (char *)body);
ret_body = std::string(body);

}

/**
 * buildSendRequestJson
 * base64url encoding
 */
void buildSendRequestJson(std::string msg, std::string &request)
{

// over 1MB when image
    std::string b64 = base64url_encode(msg);

    request = std::string( "{ \"raw\": \"" ) 
    + b64 + std::string( "\" }" );

}

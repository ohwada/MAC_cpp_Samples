#pragma once
/**
 *  outh_read_refresh_token.hpp
 * 2022-06-01 K.OHWADA
 */


#include "json_oauth.hpp"
#include "poco_file_stream.hpp"

// prototype
bool readRefreshToken(std::string filepath,  std::string &refresh_token, std::string &error);


/**
 *   read_refresh_token
 */
bool readRefreshToken(std::string filepath,  std::string &refresh_token, std::string &error)
{

    std::string text = file_text_read( filepath);
    if( text.empty() ){
        error = std::string("cannot read: ") + filepath;
        return false;
    }

    std::string access_token;
    std::string scope;
    std::string token_type;

    return parseRefreshTokenJson( text, 
refresh_token,  access_token, scope, token_type, error);
}


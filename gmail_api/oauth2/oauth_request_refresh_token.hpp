#pragma once
/**
 * oauth_request_refresh_token.hpp
 * 2022-06-01 K.OHWADA
 */


#include "oauth_request_sender.hpp"
#include "poco_file_stream.hpp"
#include "config.hpp"


// prototype
void sendRequestRefreshToken(std::string auth_code, std::string scope);
void save_refresh_token(std::string text);


/**
 *   sendRequestRefreshToken
 */
void sendRequestRefreshToken(std::string auth_code, std::string scope )
{
    if( auth_code.size() ==0){
        return;
    }
    if( scope.size() == 0 ) {
        return;
    }

    std::string response;
    std::string error;
    bool is_verbose = true;

    bool ret = send_request_refresh_token(auth_code, scope, PORT, response, error, is_verbose );

    if(ret){
        if ( isRefreshTokenJson( response) ) {
            save_refresh_token(response);
        }
    }

}


/**
 *  save_refresh_token
 */
void save_refresh_token(std::string text)
{
    file_text_write(FILE_REFRESH,  text );
}


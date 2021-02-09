#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// getNewAccessToken

#include <iostream>
#include <string>
#include "auth_token.hpp"
#include "json_auth.hpp"
#include "file_util.hpp"
#include "mail_directory.h"


// prototype
bool getNewAccessToken( std::string scope,
std::string refresh_file, 
std::string &ret_access_token, 
std::string &ret_error, 
bool is_access_save, bool is_verbose);
bool getScopeRefreshTokenToFile(std::string scope, std::string client_id, std::string client_secret,  std::string refresh_file, std::string &ret_error, bool is_verbose);






/**
 *  getNewAccessToken
 */
bool getNewAccessToken(std::string scope,
std::string refresh_file, 
std::string &ret_access_token, 
std::string &ret_error, 
bool is_access_save, bool is_verbose)
{

    const std::string ACCESS_FILE(
     "access_token.json" );

    std::string client_file =
    getMailDir() + std::string( "/client_credentials.json" );

    // char* refresh_file = (char *)str_refresh_file.c_str();

    std::string client_id;
    std::string client_secret;
    std::string error;

    bool ret1 = readClientJsonFile( client_file, client_id, client_secret, error);
    if( !ret1 ){
        ret_error = std::string("readClientJsonFile: ") +error;
        return false;
    }

    // char* client_id = (char *)str_client_id.c_str();
    // char* client_secret = (char *)str_client_secret.c_str();

    if(is_verbose){
        std::cout << "client_id: " << client_id << std::endl;
        std::cout << "client_secret: " << client_secret << std::endl;
    }

    bool ret2 = existsFile( refresh_file );
    if( !ret2 ){
    // get new, if not exists
        int ret3 =  getScopeRefreshTokenToFile( scope, 
        client_id, client_secret,  refresh_file, error, is_verbose );
        if(ret3) {
                if(is_verbose) {
                    std::cout << "save to: " << refresh_file << std::endl;
                }
        } else {
                ret_error = std::string("getScopeRefreshTokenToFile: ") +error;
                return false;
        }
    }

    std::string refresh_token;
    bool  ret4 = readRefreshTokenJsonFile( refresh_file, refresh_token, error);

    if(!ret4){
            ret_error = std::string(" readRefreshTokenJsonFile: ") +error;
        return false;
    }


    if(is_verbose){
        std::cout << "refresh_token: " << refresh_token << std::endl;
    }

    std::string access_request;
    buildAccessTokenRequest( client_id, client_secret, refresh_token, access_request );

    if(is_verbose){
        std::cout << "access_request: " << access_request << std::endl;
    }

    std::string access_response;
    bool  ret5 = getAccessToken(access_request, access_response, error, is_verbose);

    if( !ret5 ){
            ret_error = std::string("getAccessToken: ") +error;
        return false;
    }

    if(is_access_save){
        bool ret6 =  writeTextFile( ACCESS_FILE, access_response );
        if( ret6 ){
            if(is_verbose){
                std::cout << "saved: " << ACCESS_FILE << std::endl;
            }
        }
    }

    std::string access_token;
    bool ret7 = parseAccessTokenJson( access_response, access_token, error);
    if(!ret7){
           ret_error = std::string("parseAccessTokenJson: ") +error;
        return false;
    }

    ret_access_token = access_token;
    return true;
}



/**
 *  getScopeRefreshTokenToFile
 */
bool getScopeRefreshTokenToFile(std::string scope, std::string client_id, std::string client_secret,  std::string refresh_file, std::string &ret_error, bool is_verbose)
{

    std::string auth_url;
    std::string auth_code;
    std::string refresh_request;

    buildAuthorizationCodeUrl(scope, client_id, auth_url);

    if(is_verbose){
     std::cout << "auth_url: "<< auth_url << std::endl;
    }

    bool ret1 = getEnterAuthorizationCode(auth_url, auth_code);
    if(!ret1) {
        return false;
    }

    if(is_verbose){
        std::cout << " auth_code: "<<  auth_code << std::endl;
    }

     buildRefreshTokenRequest(client_id, client_secret, auth_code, refresh_request);

    if(is_verbose){
        std::cout << "refresh_request: "<< refresh_request << std::endl;
    }

    std::string error;
    bool  ret2 = getRefreshTokenToFile(refresh_request, refresh_file, error, is_verbose);

    if(!ret2) {
           ret_error = std::string("getRefreshTokenToFile: ") +error;
        return false;
    }

    return true;
}


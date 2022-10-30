#pragma once
/**
 * request_sender.hpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include  "oauth_request_builder.hpp"
#include  "curl_https_post_write.hpp"
#include  "poco_client_saver.hpp"

// global
const std::string URL_TOKEN("https://oauth2.googleapis.com/token");


// prototype
bool getNewAccessToken(std::string &access_token, 
    std::string &error, bool is_verbose );
bool send_request_refresh_token( std::string auth_code, std::string scope, int port, std::string &response, std::string &error, bool is_verbose );
bool send_request_access_token(std::string &response, 
std::string &error, bool is_verbose );
void printAccessToken(std::string token);

 
/**
 *  getNewAccessToken
 */
bool getNewAccessToken(std::string &access_token, 
    std::string &error, bool is_verbose )
{

    std::string response;
    bool ret1 = send_request_access_token(response, 
    error, is_verbose);

    if( !ret1 ){
        return false;
    }

    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    std::string scope;
    std::string token_type;

    bool ret2 = parseAccessTokenJson( response, access_token, scope, token_type, error);
    if( !ret2 ){
        return false;
    }

    std::cout << "scope: " << scope << std::endl;
    std::cout << "token_type: " << token_type << std::endl;

    return true;
}


/**
 * send_request_refresh_token
 */
bool send_request_refresh_token( std::string auth_code, std::string scope, int port, std::string &response,  std::string &error, bool is_verbose )
{

    std::string request;

    bool  ret1 = buildRefreshTokenRequestClient(auth_code, port, request, error);
    if( !ret1 ){
        return false;
    }

    std::cout << "request" << std::endl;
    std::cout << request << std::endl;

    save_request(request);

    bool is_verify = true;

    bool ret2 = https_post_form_to_memory( URL_TOKEN, request, response, error, is_verify, is_verbose );

    if(!ret2){	
        return false;
    }	

    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    save_response(response);

    return true;
}


/**
 * send_request_access_token
 */
bool send_request_access_token(std::string &response, 
std::string &error, bool is_verbose )
{

    std::string request;
 
    bool  ret1 = buildAccessTokenRequestClientRefresh( request, error);
    if( !ret1 ){
        return false;
    }

    std::cout << "request" << std::endl;
    std::cout << request << std::endl;

    save_request(request);

    bool is_verify = true;

    bool ret2 = https_post_form_to_memory( URL_TOKEN, request, response, error, is_verify, is_verbose );

    if(!ret2){	
        return false;
    }	

    std::cout << "response" << std::endl;
    std::cout << response << std::endl;

    save_response(response);

    return true;
}

/**
 * printAccessToken
 */
void printAccessToken(std::string access_token)
{
    std::cout << std::endl;
    std::cout << "access_token: " << std::endl;
    std::cout << access_token << std::endl;

}


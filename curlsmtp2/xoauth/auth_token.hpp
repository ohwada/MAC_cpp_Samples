#pragma once
/**
  * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// function for xoauth

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8



#include <string>
#include <vector> 
#include <fstream>
#include "curl_http_post_write.h"


// prototype
void buildAuthorizationCodeUrl(std::string scope, std::string client_id, std::string &auth_url);
bool getEnterAuthorizationCode(std::string url, std::string &auth_code);
void  buildRefreshTokenRequest(std::string client_id, std::string client_secret, std::string auth_code, std::string &data);
void buildAccessTokenRequest( std::string client_id, std::string client_secret, std::string refresh_token,  std::string &request );
bool  getRefreshTokenToFile(std::string postfileds, std::string file, std::string &ret_error, bool is_verbose);
bool  getAccessToken(std::string postfileds, std::string &ret_response, std::string &ret_error, bool is_verbose);



// global
const std::string URL_TOKEN( 
    "https://accounts.google.com/o/oauth2/token" );


const std::string REDIRECT_URI(
    "urn:ietf:wg:oauth:2.0:oob" );

const std::string SCOPE_MAIL( 
    "https://mail.google.com/" );

const std::string SCOPE_READONLY(
    "https://www.googleapis.com/auth/gmail.readonly" );

const std::string SCOPE_SEND( 
    "https://www.googleapis.com/auth/gmail.send" );


/**
 * buildAuthorizationCodeUrl
 */
void buildAuthorizationCodeUrl(std::string scope, std::string client_id, std::string &auth_url)
{

    const std::string URL( 
    "https://accounts.google.com/o/oauth2/auth" );

    const std::string RESPONSE_TYPE( "code" );

    const std::string APPROVAL_PROMPT( "force" );

    const std::string ACCESS_TYPE( "offline" );

    auth_url = URL
    + "?client_id="+ client_id
    + "&scope=" + scope
    + "&response_type=" + RESPONSE_TYPE
    + "&approval_prompt=" + APPROVAL_PROMPT
     + "&access_type=" + ACCESS_TYPE
    +  "&redirect_uri=" + REDIRECT_URI;

}


/**
 * getEnterAuthorizationCode
 */
bool getEnterAuthorizationCode(std::string url, std::string &auth_code)
{
    std::string code;
    code.clear();

    std::cout << "Enter the following URL into a browser:" << std::endl;
    std::cout <<  url << std::endl;
    std::cout << std::endl;
    std::cout << "Enter the browser's response to confirm authorization: ";

// enter code
    std::cin >> code;

    bool ret;
    if ( code.empty() ) {
        ret = false;
    } else {
        auth_code = code;
        ret = true;
    }

    return ret;
}


/**
 * buildRefreshTokenRequest
 */
void  buildRefreshTokenRequest(std::string client_id, std::string client_secret, std::string auth_code, std::string &data)
{

    const std::string TYPE = "grant_type=authorization_code";

    data = TYPE
    + "&client_id=" + client_id
    + "&client_secret=" + client_secret
    + "&code=" + auth_code 
    +  "&redirect_uri=" + REDIRECT_URI;

}


/**
 * buildAccessTokenRequest
 */
void buildAccessTokenRequest( std::string client_id, std::string client_secret, std::string refresh_token, std::string &request )
{
    std::string TYPE = "grant_type=refresh_token";

    request = TYPE
    + "&client_id=" + client_id 
    + "&client_secret=" + client_secret 
    + "&refresh_token=" + refresh_token ;

}

 
/**
 *  getRefreshTokenToFile
 */
bool  getRefreshTokenToFile(std::string postfileds, std::string file, std::string &ret_error, bool is_verbose)
{

    char error[100];

    bool ret = http_post_to_file( 
    (char *)URL_TOKEN.c_str(), 
    (char *)postfileds.c_str(), 
    (char *)file.c_str(), 
    (char *)error,
    is_verbose);

    if(!ret){
        ret_error = std::string(error);
        return false;
    }

    return true;
}


/**
 *  getAccessToken
 */
bool  getAccessToken(std::string postfileds, std::string &ret_response, std::string &ret_error, bool is_verbose)
{
    char error[100];

    struct CurlMemory mem;

    bool ret = http_post_to_memory(
    (char *)URL_TOKEN.c_str(), 
    (char *)postfileds.c_str(), 
    &mem,
    (char *)error,  
    is_verbose);

       if(!ret){
        ret_error = std::string(error);
        return false;
    }

    ret_response = std::string( mem.memory );
    return true;
}



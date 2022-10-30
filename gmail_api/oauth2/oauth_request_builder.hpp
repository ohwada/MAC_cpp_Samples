#pragma once
/**
 * oauth_request_builder.hpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include "Poco/Format.h"
#include "json_oauth.hpp"
#include "oauth_read_refresh_token.hpp"
#include "config.hpp"


// prototype
bool buildAuthorizationCodeUrlClient(std::string scope, int port, std::string &auth_url, std::string &error);
std::string buildAuthorizationCodeUrl(std::string scope, std::string client_id, std::string redirect_uri);
std::string get_localhost_redirect_uri(int port);
bool  buildRefreshTokenRequestClient(std::string auth_code, int port, std::string &request, std::string &error);
std::string  buildRefreshTokenRequest(std::string client_id, std::string client_secret, std::string auth_code, std::string redirect_uri);
bool  buildAccessTokenRequestClientRefresh(std::string &request, std::string &error);
std::string buildAccessTokenRequest( std::string client_id, std::string client_secret, std::string refresh_token);
void printEnterUrl(std::string url);


// global
const std::string SCOPE_MAIL( 
    "https://mail.google.com/" );

const std::string SCOPE_READONLY(
    "https://www.googleapis.com/auth/gmail.readonly" );

const std::string SCOPE_SEND( 
    "https://www.googleapis.com/auth/gmail.send" );


/**
 * buildAuthorizationCodeUrlClient
 */
bool buildAuthorizationCodeUrlClient(std::string scope, int port, std::string &auth_url, std::string &error)
{
    
    std::string client_id;
    std::string client_secret;

    bool ret = readClientJsonFileMailDir(client_id, client_secret, error);
    if(!ret ){
        return false;
    }

    // std::cout << client_id << std::endl;
    // std::cout <<  client_secret << std::endl;

    std::string  redirect_uri = get_localhost_redirect_uri(port);

    auth_url = buildAuthorizationCodeUrl(scope, client_id, redirect_uri);

    return true;
}


/**
 * buildAuthorizationCodeUrl
 */
std::string buildAuthorizationCodeUrl(std::string scope, std::string client_id, std::string redirect_uri)
{
// https://developers.google.com/identity/protocols/oauth2/native-app#identify-access-scopes

std::string FORMAT
("https://accounts.google.com/o/oauth2/v2/auth?response_type=code&scope=%s&client_id=%s&redirect_uri=%s&ack_oob_shutdown=2022-08-31");

// code_challenge
// state

    std::string auth_url;
     Poco::format(auth_url, FORMAT, scope, client_id, redirect_uri);

    return auth_url;
}


/**
 * get_localhost_redirect_uri
 */
std::string get_localhost_redirect_uri(int port)
{
    const std::string FORMAT("http://127.0.0.1:%d");

    std::string url;
    Poco::format( url, FORMAT, port );

    return url;
}


/**
 * buildRefreshTokenRequestClient
 */
bool  buildRefreshTokenRequestClient(std::string auth_code, int port, std::string &request, std::string &error)
{
    std::string redirect_uri = get_localhost_redirect_uri(port);

    std::string client_id;
    std::string client_secret;

    bool ret = readClientJsonFileMailDir(client_id, client_secret, error);
    if(!ret){
        return false;
    }

     request = buildRefreshTokenRequest(client_id, client_secret, auth_code, redirect_uri);

        return true;
}


/**
 * buildRefreshTokenRequest
 */
std::string  buildRefreshTokenRequest(std::string client_id, std::string client_secret, std::string auth_code, std::string redirect_uri)
{
// ok
    const std::string TYPE = "grant_type=authorization_code";

    std::string request = 
    TYPE
    + "&client_id=" + client_id
    + "&client_secret=" + client_secret
    + "&code=" + auth_code 
    +  "&redirect_uri=" + redirect_uri;

    return request;
}


/**
 * buildAccessTokenRequestClientRefresh
 */
bool  buildAccessTokenRequestClientRefresh(std::string &request, std::string &error)
{
    
    std::string client_id;
    std::string client_secret;

    bool ret1 = readClientJsonFileMailDir(client_id, client_secret, error);
    if(!ret1){
        return false;
    }

    std::string refresh_token;
  
    bool ret2 = readRefreshToken(FILE_REFRESH, refresh_token, error);
    if(!ret2){
        return false;
    }

    request = buildAccessTokenRequest( client_id, client_secret, refresh_token);

    return true;
}


/**
 * buildAccessTokenRequest
 */
std::string buildAccessTokenRequest( std::string client_id, std::string client_secret, std::string refresh_token)
{

const std::string FORMAT("client_id=%s&client_secret=%s&refresh_token=%s&grant_type=refresh_token");

    std::string request; 
    Poco::format(request, FORMAT, client_id, client_secret , refresh_token);

    return request; 
}


/**
 * printEnterUrl
 */
void printEnterUrl(std::string url)
{
    std::cout << std::endl;

    std::cout << "Please Enter the following URL into Browser:" << std::endl;

    std::cout <<  url << std::endl;

}


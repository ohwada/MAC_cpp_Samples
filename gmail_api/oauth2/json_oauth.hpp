#pragma once
/**
  * json_oauth.hpp
 * 2022-06-01 K.OHWADA
 */

// readClientJsonFile

#include <fstream>
#include <string>
#include "json/json.h"
#include "mail_directory.h"


// prototype
bool readClientJsonFileMailDir(std::string &client_id, std::string &client_secret, std::string &error);
bool readClientJsonFile( std::string filepath, std::string &client_id, std::string &client_secret, std::string &error);
bool isRefreshTokenJson( std::string text);
bool  parseRefreshTokenJson( std::string json, std::string &refresh_token, 
std::string &access_token, 
std::string &scope, 
std::string &token_type, 
std::string &error); 
bool parseAccessTokenJson(std::string json, std::string &access_token, 
std::string &scope, 
std::string &token_type, 
std::string &error);


/**
 * readClientJsonFileMailDir
 */
bool readClientJsonFileMailDir(std::string &client_id, std::string &client_secret, std::string &error) 
{
    std::string filepath =
    getMailDir() + std::string( "/client_credentials.json" );

    return readClientJsonFile(filepath,  client_id, client_secret, error); 
}


/**
 * readClientJsonFile
 */
bool readClientJsonFile( std::string filepath, std::string &client_id, std::string &client_secret, std::string &error) 
{
    Json::Value root;
   std::ifstream ifs;

    ifs.open(filepath);
    if(!ifs){
        error = "can not open: " + filepath;
     return false;
    }

    Json::CharReaderBuilder builder;
    // builder["collectComments"] = true;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        error = errs;
        return false;
  }

    Json::Value installed = root.get("installed",  Json::nullValue );
    if(installed.isNull() ){
        error = "not found installed";
        return false;
    }

    Json::Value jv_client_id = installed.get("client_id",  Json::nullValue );
    Json::Value jv_client_secret = installed.get("client_secret",  Json::nullValue );

    if(jv_client_id.isNull() ){
        error = "not found client_id";
        return false;
    } else {
        client_id = jv_client_id.asString();
    }

   if( jv_client_secret.isNull() ){
        error = "not found client_secret";
        return false;
    } else {
        client_secret = jv_client_secret.asString();	
    }

    return true;
}


/**
 * isRefreshTokenJson
 */
bool isRefreshTokenJson( std::string text)
{

    std::string refresh_token;
    std::string access_token;
    std::string scope;
    std::string token_type;
    std::string error;

    return parseRefreshTokenJson( text, 
    refresh_token, access_token, scope, token_type, error);
}


/**
 * parseRefreshTokenJson
 */
bool  parseRefreshTokenJson( std::string json, std::string &refresh_token, 
std::string &access_token, 
std::string &scope, 
std::string &token_type, 
std::string &error) 
{
    Json::Value root;
    JSONCPP_STRING err;

    const auto  length = 
    static_cast<int>( json.length());

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    char const * 	begin = json.c_str();
    char const * 	end = json.c_str() +  length;

    if (!reader->parse( begin,  end, &root,
                       &err)) {
        error = "cannot parse: " + err;
        return false;
    }

    if(root.isNull() ){
        error = "cannot parse";
        return false;
    }

    Json::Value jv_refresh_token = root.get("refresh_token",  Json::nullValue );
    if(jv_refresh_token.isString() ){
        refresh_token = jv_refresh_token.asString();
    } else {
        error = "not found refresh_token";
        return false;
    }

   Json::Value jv_access_token = root.get("access_token",  Json::nullValue );
    if(jv_access_token.isString() ){
            access_token = jv_access_token.asString();
    }


   Json::Value jv_scope = root.get("scope",  Json::nullValue );
    if(jv_scope.isString() ){
            scope = jv_scope.asString();
    }

   Json::Value jv_token_type = root.get("token_type",  Json::nullValue );
    if(jv_token_type.isString() ){
            token_type = jv_token_type.asString();
    }

    return true;
}


/**
 * parseAccessTokenJson
 */
bool parseAccessTokenJson(std::string json, std::string &access_token, std::string &scope, std::string &token_type, std::string &error)
{

    Json::Value root;
    JSONCPP_STRING err;

    const auto  length = 
    static_cast<int>( json.length());

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

char const * 	begin = json.c_str();
char const * 	end = json.c_str() +  length;

    if (!reader->parse( begin,  end, &root,
                       &err)) {
        error = "cannot parse: " + err;
        return false;
    }

    if(root.isNull() ){
        error = "cannot parse";
        return false;
    }


Json::Value jv_access_token = root.get("access_token",  Json::nullValue );
    if(jv_access_token.isString() ){
            access_token = jv_access_token.asString();
    } else {
        error = "not found access_token";
        return false;
    }


   Json::Value jv_scope = root.get("scope",  Json::nullValue );
    if(jv_scope.isString() ){
            scope = jv_scope.asString();
    }

   Json::Value jv_token_type = root.get("token_type",  Json::nullValue );
    if(jv_token_type.isString() ){
            token_type = jv_token_type.asString();
    }

    return true;
}

#pragma once
/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// readClientJsonFile

#include <fstream>
#include <string>
#include "json/json.h"



// prototype
bool readClientJsonFile( std::string filepath, std::string &client_id, std::string &client_secret, std::string &error);
bool  readRefreshTokenJsonFile( std::string filepath, std::string &refresh_token, std::string &error);
bool parseAccessTokenJson(std::string json, std::string &access_token, std::string &error);



/**
 * readClientJsonFile
 */
bool readClientJsonFile( std::string filepath, std::string &client_id, std::string &client_secret, std::string &error) 
{
    Json::Value root;
   std:: ifstream ifs;

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
 * readRefreshTokenJsonFile
 */
bool  readRefreshTokenJsonFile( std::string filepath, std::string &refresh_token, std::string &error) 
{
    Json::Value root;
   std:: ifstream ifs;

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

    Json::Value jv_refresh_token = root.get("refresh_token",  Json::nullValue );

    if(jv_refresh_token.isNull() ){
        error = "not found refresh_token";
        return false;
    } else {
        refresh_token = jv_refresh_token.asString();
    }

    return true;
}


/**
 * parseAccessTokenJson
 */
bool parseAccessTokenJson(std::string json, std::string &access_token, std::string &error)
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
        error = err;
        return false;
    }

    Json::Value jv_access_token = root.get("access_token",  Json::nullValue );


    if(jv_access_token.isNull() ){
        error = "not found access_token";
        return false;
    } else {
        access_token = jv_access_token.asString();
    }

    return true;
}

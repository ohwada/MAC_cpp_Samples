#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// readMessageResponseJsonFile

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json/json.h"


// prototype
bool parseListResponseJson( std::string json, std::vector<std::string> &vec, std::string &error, 
bool is_verbose);


/**
 * parseListResponseJson
 */
bool parseListResponseJson( std::string json, std::vector<std::string> &vec, std::string &error, 
bool is_verbose) 
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

    Json::Value messages = root["messages"];
    if( messages.isNull() ){
        error = "not found messages";
        return false;
    }


    for ( int index = 0; index < messages.size(); ++index ){
        Json::Value msg = messages[index];
         Json::Value jv_id = msg["id"];
        if( !jv_id.isNull() ){
            std::string id = jv_id.asString();
            vec.push_back(id);
        }

        if(is_verbose){
            std::cout << index << " : " << jv_id << std::endl;
        }
    } // for

    return true;
}


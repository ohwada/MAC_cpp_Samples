#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */


// readGmailJsonFile


#include <fstream>
#include <string>
#include "json/json.h"



// prototype
bool readAttchmentJsonFile( std::string filepath, 
std::string &data, int *size, std::string &error ) ;


/**
 * readAttachmentJsonFile
 */
bool readAttchmentJsonFile( std::string filepath, 
std::string &data, int *size, std::string &error ) 
{

// JSON representation
// {
//  "attachmentId": string,
//  "size": integer,
//  "data": string
// A base64-encoded string.
//}

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

    bool is_error = false;

    Json::Value jv_size = root.get("size",  Json::nullValue );
   if(jv_size.isNull() ){
        error = "not found size \n";
        is_error = true;
    } else {
        *size = jv_size.asInt();
    }

    Json::Value jv_data = root.get("data",  Json::nullValue );
   if(jv_data.isNull() ){
        error += "not found data \n";
        is_error = true;
    } else {
        data = jv_data.asString();
    }

    return !is_error;
}


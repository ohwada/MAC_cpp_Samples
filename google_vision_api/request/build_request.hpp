#pragma once
/**
 * build_request.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include "file_util.hpp"
#include "base64.hpp"

// prototype
bool build_request_from_file(std::string filepath, int num, std::string &ret_request);
std::string build_request_from_bytes(std::string bytes, int num);
std::string build_request_from_b64(std::string b64, int num);


/**
 * build_request_from_file
 */
bool build_request_from_file(std::string filepath, int num, std::string &ret_request)
{
    if( !existsFile(filepath) ){
        return false;
    }

    std::string bytes;

    bool ret = readBinaryFile2(filepath,  bytes);
    if(!ret){
        return false;
    }


    std::string request = build_request_from_bytes(bytes, num);
    ret_request = request;

    return true;
}


/**
 * build_request_from_bytes
 */
std::string build_request_from_bytes(std::string bytes, int num)
{
    std::string b64;
    encodeB64(bytes, b64);

    return build_request_from_b64(b64, num);
}


/**
 * build_request_from_b64
 */
std::string build_request_from_b64(std::string b64, int num)
{

std::string features =
R"( "features": [ { 
  "maxResults" : )"
+ std::to_string(num)
+  R"(, "type" : "FACE_DETECTION" } ] )";

std::string images =
    R"( "image": { "content": ")" 
    + b64
    + R"(" }, )";

std::string request =  
R"( { "requests": [ { )"
+ images
+ features
+ R"( } ] } )";

    return request;
}



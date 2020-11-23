#pragma once
/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

#include <string>
#include "gmail_api_request.hpp"
#include "response_list_json.hpp"
#include "response_msg_json.hpp"
#include "file_util.hpp"


// prototype
bool getListResponse(bool is_new, std::string access_token, std::string &ret_response, bool verbose);
bool getMsgResponse(bool is_new, std::string id, std::string access_token, std::string &ret_response, bool verbose);

/**
 * getListResponse
 */
bool getListResponse(bool is_new, std::string access_token, std::string &ret_response, bool verbose)
{

    const std::string FILE_LIST_RESPONSE( "list_response.json" );

    bool res = false;
    std::string response;
    std::string error;

    if( is_new && !access_token.empty() ) {

           bool ret1 = api_list_request( access_token, 
            response, error, verbose);
            if(ret1) {
                res = true;
                ret_response = response;

                bool ret2 = writeTextFile(FILE_LIST_RESPONSE, response);

                if( ret2 ){
                    std::cout << "saved to: " << FILE_LIST_RESPONSE << std::endl;
                } else {
                    std::cout << "writeTextFile faild: " << FILE_LIST_RESPONSE << std::endl;
                } //  if ret2     
            } //  if ret1     
   
     } else if( existsFile( FILE_LIST_RESPONSE ) ) {

            bool ret3 =readTextFile(FILE_LIST_RESPONSE, response);
            if( ret3) {
                res = true;
                ret_response = response;
            } else {
                std::cout << "readTextFile faild: " << FILE_LIST_RESPONSE << std::endl;
            } // if ret3
 
    } //     if is_new

    return res;
}


/**
 * getMsgResponse
 */
bool getMsgResponse(bool is_new, std::string id, std::string access_token, std::string &ret_response, bool verbose)
{

    std::string file = std::string("msg_") + id + std::string(".json");

    bool res = false;

    std::string response;
    std::string error;

    if( is_new && !access_token.empty() ) {

            bool ret1 = api_msg_request(id, access_token,  response,  error, verbose );

            if( ret1 ){
                res = true;
                ret_response = response;
            } else {
                std::cout << error << std::endl;
            }

            bool ret2 = writeTextFile( file, response);

            if(ret2){
                    std::cout << "saved to: " << file << std::endl;
            } else {
                    std::cout << "writeTextFile faild: " << file << std::endl;
            } // ret2

    } else if(  existsFile(file) ) {

            bool ret3 = readTextFile( file, response);
            if( ret3 ){
                res = true;
                ret_response = response;
            } else {
                std::cout << "readTextFile faild: " << file << std::endl;
            } // if ret3

    } // if is_new

    return res;
}


#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// get message list and first one message with Google API

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


#include <string>
#include "curl_http_token.hpp"
#include "curl_http_json_post_token.hpp"


const std::string URL_API_MESSAGES( "https://www.googleapis.com/gmail/v1/users/me/messages" );

const std::string URL_API_SEND( "https://www.googleapis.com/gmail/v1/users/me/messages/send" );


// prototype
bool api_list_request( std::string access_token, std::string &response, std::string &error, bool is_verbose );
bool api_msg_request( std::string id, std::string access_token, std::string &responsr, std::string &error, bool is_verbose);
bool api_send_request( std::string request, std::string access_token, std::string &response, std::string &error, bool is_verbose);
bool api_attachment_request_to_file( std::string msg_id, std::string atachment_id, std::string access_token, std::string file, std::string &error, bool is_verbose);

/**
 * api_list_request
 */
bool api_list_request( std::string access_token, std::string &ret_response, std::string &ret_error, bool is_verbose)
{

   std::string response;
    std::string error;

    bool ret = http_token_to_memory(
    URL_API_MESSAGES,
    access_token, 
    response, 
    error, 
    is_verbose);

    if(ret){
        ret_response = response;
    } else {
        ret_error = error;
    }

    return ret;
}


/**
 * api_msg_request
 */
bool api_msg_request( std::string id, std::string access_token, std::string &ret_response, std::string &ret_error, bool is_verbose)
{

    std::string url = URL_API_MESSAGES + std::string("/") +id;

     if(is_verbose) {
        std::cout << "url: " << url << std::endl;
    }

    std::string response;
    std::string error;

    bool ret = http_token_to_memory(
    url,
    access_token, 
    response, 
    error, 
    is_verbose);

    if(ret){
        ret_response = response;
    } else {
        ret_error = error;
    }

    return ret;
}


/**
 * api_send_request
 */
bool api_send_request( std::string request,  std::string access_token, std::string &ret_response,  std::string &ret_error, bool is_verbose)
{
    std::string response;
    std::string error;

    bool ret =  http_json_post_token_to_memory(
    URL_API_SEND, 
    request, 
    access_token, 
    response,  
    error, 
    is_verbose );

    if(ret) {
        ret_response = response;
    } else {
        ret_error = error;
    }

    return ret;
}


/**
 * api_attachment_request_to_file
 */
bool api_attachment_request_to_file( std::string msg_id, std::string attach_id, std::string access_token, std::string file, std::string &ret_error, bool is_verbose)
{

// GET https://gmail.googleapis.com/gmail/v1/users/{userId}/messages/{messageId}/attachments/{id}

    std::string url = URL_API_MESSAGES + std::string("/") +msg_id + std::string("/attachments/") + attach_id;


     if(is_verbose) {
        std::cout << "url: " << url << std::endl;
    }

    std::string response;
    std::string error;

    bool ret = http_token_to_file(
    url,
    access_token, 
    file, 
    error, 
    is_verbose);

    if(!ret){
        ret_error = error;
    }

    return ret;

}


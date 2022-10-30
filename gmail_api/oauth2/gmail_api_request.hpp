#pragma once
/**
 * gmail_api_request.hpp
 * 2022-06-01 K.OHWADA
 */

// get message list and first one message with Google API

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


#include <string>
#include "gmail_api_request_builder.hpp"
#include "curl_http_token.hpp"
#include "curl_http_json_post_token.hpp"
#include "poco_timestamp.hpp"
#include "poco_file_stream.hpp"

// https://developers.google.com/gmail/api/reference/rest#service-endpoint

// GET
const std::string URL_API_MESSAGES( "https://www.googleapis.com/gmail/v1/users/me/messages" );

// POST
const std::string URL_API_SEND( 
"https://www.googleapis.com/gmail/v1/users/me/messages/send" );



// prototype
bool api_list_request( std::string access_token, std::string &response, std::string &error, bool is_verbose );
bool api_msg_request( std::string id, std::string access_token, std::string &responsr, std::string &error, bool is_verbose);
bool api_mail_send( std::string request, std::string access_token, std::string &response, std::string &error, bool is_verbose);
bool api_attachment_request_to_file( std::string msg_id, std::string atachment_id, std::string access_token, std::string file, std::string &error, bool is_verbose);
bool save_api_request(std::string data);
bool save_api_response(std::string data);


/**
 * api_list_request
 */
bool api_list_request( std::string access_token, std::string &response, std::string &error, bool is_verbose)
{

    bool ret = http_token_to_memory(
    URL_API_MESSAGES,
    access_token, 
    response, 
    error, 
    is_verbose);

    if(ret){
        save_api_response(response);
    } 

    return ret;
}


/**
 * api_msg_request
 */
bool api_msg_request( std::string id, std::string access_token, std::string &response, std::string &error, bool is_verbose)
{

    std::string url =  build_api_msg_request(
URL_API_MESSAGES, id);

     if(is_verbose) {
        std::cout << "url: " << url << std::endl;
    }

    bool ret = http_token_to_memory(
    url,
    access_token, 
    response, 
    error, 
    is_verbose);

    if(ret){
        save_api_response(response);
    }

    return ret;
}


/**
 * api_mail_send
 */
bool api_mail_send( std::string request,  std::string access_token, std::string &response,  std::string &error, bool is_verbose)
{

    save_api_request(request);

    bool ret =  http_json_post_token_to_memory(
    URL_API_SEND, 
    request, 
    access_token, 
    response,  
    error, 
    is_verbose );

    if(ret) {
        save_api_response(response);
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


/**
 * save_api_request
 */
bool save_api_request(std::string data)
{
    std::string dir("log");
    std::string prefix("api_request");
    std::string ext("txt"); 

     std::string path= build_timestamp_file_path(dir, prefix, ext);

    return  file_text_write(path,  data );
}


/**
 * save_api_response
 */
bool save_api_response(std::string data)
{
    std::string dir("log");
    std::string prefix("api_response");
    std::string ext("txt"); 

       std::string path= build_timestamp_file_path(dir, prefix, ext);
   
    return file_text_write(path,  data );
}

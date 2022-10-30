#pragma once
/**
 * curl_http_json_post_token.hpp
 * 2022-06-01 K.OHWADA
 */

// send mail with Google API

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


#include <string>
#include "gmail_http_header_builder.hpp"
#include "curl_write_func.hpp"


// prototype
bool http_json_post_token_to_memory(std::string url, std::string postfileds, std::string access_token, std::string &response, std::string &error,  bool is_verbose );


/**
 *  http_json_post_token_to_memory
 */
bool http_json_post_token_to_memory(std::string url, std::string postfileds, std::string access_token, std::string &response,  std::string &error,  bool is_verbose)
{

	const std::string HEADER_CONTENT_TYPE_JSON(
	"Content-Type: application/json; charset=utf-8");

	std::string hdr_auth =
    build_header_authorization(access_token);

	std::list<std::string> header; 

    header.push_back(HEADER_CONTENT_TYPE_JSON);
	header.push_back(hdr_auth);

    bool is_verify = true;
   
	return https_post_to_memory_header(url,  postfileds,  	header, response,  error,  is_verify, is_verbose );
}


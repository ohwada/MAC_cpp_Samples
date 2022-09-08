#pragma once
/**
 * vision_api_request.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include "apikey.hpp"
#include "curl_http_json_post.hpp"


const std::string URL_API_ANNOTATE(
 "https://vision.googleapis.com/v1/images:annotate" );


// prototype
bool api_annotate_request(std::string postfileds, std::string &ret_response, std::string &ret_error, bool is_verbose);
std::string get_url();


/**
 * get_url
 */
std::string get_url()
{
    auto apikey = get_apikey();
    std::cout << apikey << std::endl;

    std::string url = URL_API_ANNOTATE
    +R"(?key=)" + apikey;

    return url;
}


/**
 * api_annotate_request
 */
bool api_annotate_request(std::string postfileds, std::string &ret_response, std::string &ret_error, bool is_verbose)
{

    auto url  = get_url();
    std::cout << url << std::endl;

    std::string response;
    std::string error;

bool ret = http_json_post_to_memory(url, 
postfileds,  response,  error, is_verbose );

    if(ret){
        ret_response = response;
    } else {
        ret_error = error;
    }

    return ret;
}


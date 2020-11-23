#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// get message list and first one message with Google API

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


#include <stdio.h>
#include <stdlib.h>
#include "curl_api_request.h"


const char URL_API_MESSAGES[] = "https://www.googleapis.com/gmail/v1/users/me/messages";

const char URL_API_SEND[] = "https://www.googleapis.com/gmail/v1/users/me/messages/send";


// prototype
bool api_list_request_to_file( char* access_token, char* filepath, char *error, bool is_verbose );
bool api_msg_request_to_file( char* id, char* access_token, char* filepath, char *error, bool is_verbose);
bool api_send_request( char *request, char *access_token, char *response, char *error, bool is_verbose);
void printResponse(char *response);



/**
 * api_list_request_to_file
 */
bool api_list_request_to_file( char* access_token, char* filepath, char *error, bool is_verbose)
{
    return http_token_to_file(
    (char *)URL_API_MESSAGES,
    access_token, 
    filepath, 
    error, is_verbose);
}

/**
 * api_msg_request_to_file
 */
bool api_msg_request_to_file( char* id, char* access_token, char* filepath, char *error, bool is_verbose)
{

    const size_t BUFSIZE = 100;
    char url[BUFSIZE];

    snprintf(url, BUFSIZE, "%s/%s", URL_API_MESSAGES, id);

     if(is_verbose){
        printf("url: %s \n", url);
    }

    return http_token_to_file(
    (char *)url,
    access_token, 
    filepath, 
    error, is_verbose);
}

/**
 * api_send_request
 */
bool api_send_request( char *request, char *access_token, char *response, char *error, bool is_verbose)
{
    struct CurlMemory mem;

    bool ret = http_json_post_token_to_memory( 
    (char* )URL_API_SEND, 
    request, 
    access_token, 
    &mem, 
    error, 
    is_verbose);

    if(!ret){
        return false;
    }

    strcpy(response, mem.memory);
    return true;
}


/**
 * printResponse
 */
void printResponse(char *response)
{
    printf("\n");
    printf("----- \n");
    printf("%s \n", response);
    printf("----- \n");
}


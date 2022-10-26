#pragma once
/**
  * request_token.h
 * 2022-06-01 K.OHWADA
 */


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "http_post_write.h"
#include "config.h"

// prototype
bool  requestRefreshTokenToFile(char* request, char* error);
bool  requestAccessToken(char * data, char * response, char *error, bool is_verbose);


const char URL_TOKEN[] = 
"https://accounts.google.com/o/oauth2/token";


/**
 *  requestRefreshTokenToFile
 */
bool  requestRefreshTokenToFile(char* request, char* error)
{

    bool is_verbose = true;

    return http_post_to_file( (char *)URL_TOKEN, request, (char *)FILE_REFRESH, error, is_verbose);

}


/**
 *  requestAccessToken
 */
bool  requestAccessToken(char * data, char * response, char *error, bool is_verbose)
{
    struct CurlMemory mem;

    bool ret = http_post_to_memory( (char *)URL_TOKEN, data, &mem, error, is_verbose);

    if(ret){
        strcpy(response , mem.memory);
    } 

    return ret;
}


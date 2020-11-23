#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// function for oauth

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h> 
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "curl_http_post_write.h"


// prototype
void buildAuthorizationCodeUrl(char* scope, char * client_id, char * buf, size_t bufsize );
bool getEnterAuthorizationCode(char * url, char * auth_code);
void  buildRefreshTokenRequest(char * client_id, char * client_secret, char * auth_code, char * buf, size_t bufsize);
void buildAccessTokenRequest( char * client_id, char * client_secret, char * refresh_token, char * data, size_t bufsize );
bool  getRefreshTokenToFile(char * data, char * file, char *error, bool is_verbose);
bool  getAccessToken(char * data, char * response, char *error, bool is_verbose);
bool getInputChars(char* buf, size_t size);


// global
const char URL_TOKEN[] = 
"https://accounts.google.com/o/oauth2/token";

const char REDIRECT_URI[] = 
"urn:ietf:wg:oauth:2.0:oob";


const char SCOPE_MAIL[] = "https://mail.google.com/";

const char SCOPE_READONLY[] = 
"https://www.googleapis.com/auth/gmail.readonly";

const char SCOPE_SEND[] = 
"https://www.googleapis.com/auth/gmail.send";





/**
 * buildAuthorizationCodeUrl
 */
void buildAuthorizationCodeUrl(char* scope, char * client_id, char * buf, size_t bufsize)
{

    const char URL[] = "https://accounts.google.com/o/oauth2/auth";

    //const char PARAM[] = "scope=https://mail.google.com/&response_type=code&approval_prompt=force&access_type=offline";

    const char PARAM[] = "response_type=code&approval_prompt=force&access_type=offline";

    snprintf(buf, bufsize, "%s?%s&scope=%s&client_id=%s&redirect_uri=%s", URL, PARAM, scope, client_id, REDIRECT_URI);

}


/**
 * getEnterAuthorizationCode
 */
bool getEnterAuthorizationCode(char * url, char * auth_code)
{

    printf("Enter the following URL into a browser: \n");
    printf("%s \n", url);
    printf("Enter the browsers response to confirm authorization: ");

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];
    bool ret = getInputChars(buf, BUFSIZE);
    if(!ret){
        return false;
    }

   strcpy(auth_code, buf);
    return true;
}


/**
 * getInputChars
 */
bool getInputChars(char* buf, size_t size)
{

    const char LF = '\n' ;
    const char END = '\0' ;

    if (fgets(buf, size, stdin) == NULL) {
        return false;
    }

    if (strchr(buf, LF) != NULL) {
// if it contains a newline character
// replace with NUL terminal
        buf[strlen(buf) - 1] = END;
    } else {
// clear the input stream
// becuase the part exceeding the maximum number of characters are left in the input stream
        while(getchar() != LF);
        return false;
    }

    return true;
}


/**
 * buildRefreshTokenRequest
 */
void  buildRefreshTokenRequest(char * client_id, char * client_secret, char * auth_code, char * buf, size_t bufsize)
{

    const char  TYPE[] = "grant_type=authorization_code";

    snprintf(buf, bufsize, "%s&client_id=%s&client_secret=%s&code=%s&redirect_uri=%s", TYPE, client_id,  client_secret, auth_code, REDIRECT_URI);

}


/**
 * buildAccessTokenRequest
 */
void buildAccessTokenRequest( char * client_id, char * client_secret, char * refresh_token, char * buf, size_t bufsize )
{
    char TYPE[] = "grant_type=refresh_token";

    snprintf(buf, bufsize, "%s&client_id=%s&client_secret=%s&refresh_token=%s", TYPE,  client_id,  client_secret, refresh_token);

}

 
/**
 *  getRefreshTokenToFile
 */
bool  getRefreshTokenToFile(char * data, char * file, char *error, bool is_verbose)
{
    return http_post_to_file( (char *)URL_TOKEN, data, file, error, is_verbose);
}


/**
 *  getAccessToken
 */
bool  getAccessToken(char * data, char * response, char *error, bool is_verbose)
{
    struct CurlMemory mem;

    bool ret = http_post_to_memory( (char *)URL_TOKEN, data, &mem, error, is_verbose);

    if(ret){
        strcpy(response , mem.memory);
    } 

    return ret;
}


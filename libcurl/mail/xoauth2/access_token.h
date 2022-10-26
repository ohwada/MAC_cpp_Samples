#pragma once
/**
  * access_toke.h
 * 2022-06-01 K.OHWADA
 */

#include <stdio.h>
#include <stdbool.h>
#include "auth_json.h"
#include "request_token.h"
#include "client_credentials.h"
#include "file_timestamp.h"
#include "file_util.h"
#include "config.h"


// prototype
bool getAccessToken(
char* access_token, char *error, bool is_verbose);
bool get_access_token(
char* access_token, char *error, bool is_verbose);
bool getAccessTokenRequest( char * request, char* error, bool is_verbose );
void build_access_token_request( char * client_id, char * client_secret, char * refresh_token, char * request );
bool save_access_token( char* data);


/**
 *  getAccessToken
 */
bool getAccessToken(
char* access_token, 
char* error,
bool is_verbose)
{

    return get_access_token(
    access_token, error,is_verbose);

}


/**
 *  get_access_token
 */
bool get_access_token(
char* access_token, 
char *error,
bool is_verbose)
{

    
    const size_t BUFSIZE = 1024;
    char access_request[BUFSIZE];
    char access_response[BUFSIZE];

    bool ret1 = getAccessTokenRequest( (char *)access_request, error, is_verbose);
    if(!ret1){
        return false;
    }

    if(is_verbose){
        printf( "\n access_request \n");
        printf( "%s \n",  access_request );
    }

    printf( "\n send request \n");
    bool  ret5 = requestAccessToken( (char *)access_request, (char *)access_response, error, is_verbose);
    if( !ret5 ){
        return false;
    }

    if(is_verbose) {
        printf("\n access_response \n");
        printf("%s \n", access_response);
    }

    save_access_token( (char *)access_response);

    bool ret7 = parseAccessTokenJson( 
(char *)access_response, access_token, error);
    if( !ret7 ){
        return false;
    }

    return true;
}


/**
 getAccessTokenRequest
 */
bool getAccessTokenRequest( char * request, char* error, bool is_verbose )
{

    const size_t BUFSIZE = 512;
    char client_id[BUFSIZE]; 
    char client_secret[BUFSIZE];
    char refresh_token[BUFSIZE];

    bool ret1 = read_client_credentials(
    (char *)client_id, (char *)client_secret, error);
    if(!ret1){
        return false;
    }

    if(is_verbose){
        printf( "client_id: %s \n",  (char *)client_id );
        printf( "client_secret: %s \n",  (char *)client_secret );
    }

    if( !file_exists( (char *)FILE_REFRESH ) ){
        strcpy(error, "not found: ");
        strcat(error, (char *)FILE_REFRESH );
        return false;
    }

    bool  ret2 = readRefreshTokenJsonFile( (char *)FILE_REFRESH, (char *)refresh_token, (char *)error);
    if(!ret2){
        return false;
    }

    if(is_verbose){
        printf( "refresh_token: %s \n",  (char *)refresh_token );
    }

    build_access_token_request( (char * )client_id, (char *) client_secret, (char * )refresh_token, request  );

    return true;
}


/**
 * build_access_token_request
 */
void build_access_token_request( char * client_id, char * client_secret, char * refresh_token, char * request )
{
// feedbackOAuth 2.0 for Mobile & Desktop Apps
// https://developers.google.com/identity/protocols/oauth2/native-app?hl=en

    const char FORMAT[] =
"grant_type=refresh_token&client_id=%s&client_secret=%s&refresh_token=%s";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, client_id,  client_secret, refresh_token);

    strcpy(request , buf);
}


/**
 *  save_access_token
 */
bool save_access_token( char* data)
{
    const size_t BUFSIZE = 512;
     char filename[BUFSIZE];
  char path[BUFSIZE];
  char error[BUFSIZE];

    char* dir = "log";
    char* prefix = "access_token";
    char* ext = "json";

    get_timestamp_filename(prefix, ext, (char *)filename );

    make_path( dir, filename, (char *)path );

    bool ret = file_text_write( (char *)path, data, error );
    if(ret){
        printf("saved: %s \n", path);
    } else {
        fprintf(stderr, "save faild: %s %s \n", path, error);
    }

    return ret;
}



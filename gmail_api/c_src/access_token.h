#pragma once
/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// getNewAccessToken


#include <stdio.h>
#include <stdbool.h>
#include "auth_json.h"
#include "auth_token.h"
#include "mail_directory.h"
#include "file_util.h"


// prototype
bool getNewAccessToken( char* scope,
char* refresh_file, 
char* access_token, 
char *error,
bool is_access_save, bool is_verbose);
bool   getScopeRefreshTokenToFile(char* scope, char * client_id, char * client_secret,  char * refresh_file, char *error, bool is_verbose);


/**
 *  getNewAccessToken
 */
bool getNewAccessToken(char* scope,
char* refresh_file, 
char* access_token, 
char *error,
bool is_access_save, bool is_verbose)
{

    const char ACCESS_FILE[] = "access_token.json";

    char client_file[100];
    strcpy( client_file, getMailDir() );
    strcat( client_file, "/client_credentials.json");

    char client_id[100];
    char client_secret[100];
    char refresh_token[100];
    char err[100];

    bool ret1 = readClientJsonFile( client_file, client_id, client_secret, err);
    if( !ret1 ){
        strcpy(error, "readClientJsonFile: ");
        strcat(error, err);
        return false;
    }

    if(is_verbose){
        printf("client_id: %s \n", client_id);
        printf("client_secret: %s \n", client_secret);
    }

    int ret2 = existsFile(  refresh_file );
    if( !ret2 ){

    // get new, if not exists
        bool ret3 =   getScopeRefreshTokenToFile(scope, 
        client_id, client_secret,  refresh_file, err, is_verbose);

        if( ret3 ){
                if(is_verbose){
                        printf( "save to: %s \n",  refresh_file );
                }
        } else {
                strcpy(error, " getScopeRefreshTokenToFile: ");
                strcat(error, err );
                return false;
        }
    }


    bool  ret4 = readRefreshTokenJsonFile( (char *)refresh_file, refresh_token, err);
    if( !ret4 ){
// can not read, immediately after writing
        strcpy(error, "readRefreshTokenJson:");
        strcat(error, err);
        return false;
    }

    if(is_verbose){
        printf( "refresh_token: %s \n",  refresh_token );
    }

    const size_t BUFSIZE = 300;
    char access_request[BUFSIZE];
    buildAccessTokenRequest( client_id, client_secret,  refresh_token, access_request, BUFSIZE );

    if(is_verbose){
        printf( "access_request: %s \n",  access_request );
    }

    char access_response[500];
    bool  ret5 = getAccessToken(access_request, access_response, err, is_verbose);
    if( !ret5 ){
        strcpy(error, "getAccessToken: ");
        strcat(error, err);
        return false;
    }

    if(is_access_save){
        int ret6 =  writeTextFile( (char *)ACCESS_FILE, access_response, error );
        if( ret6 ){
            printf("saved: %s \n", ACCESS_FILE);
        } else {
            printf( "writeTextFile: %s \n", error);
        }
    }

    bool ret7 = parseAccessTokenJson( access_response, access_token, error);
    if( !ret7 ){
        strcpy(error, "parseAccessTokenJson: ");
        strcat(error, err);
        return false;
    }

    return true;
}


/**
 *    getScopeRefreshTokenToFile
 */
bool   getScopeRefreshTokenToFile(char* scope, char * client_id, char * client_secret,  char * refresh_file, char *error, bool is_verbose)
{

    const size_t BUFSIZE = 300;
    char auth_url[BUFSIZE];

    char auth_code[200];
    char refresh_request[200];

    buildAuthorizationCodeUrl(scope, client_id, auth_url, BUFSIZE);

    bool ret1 = getEnterAuthorizationCode(auth_url, auth_code);
    if(!ret1) {
        return false;
    }

    if ( strlen(auth_code) == 0 ){
        printf("Please enter Authorization Code \n");
        return false;
    }

    if(is_verbose){
        printf("auth_code: %s \n", auth_code);
    }

     buildRefreshTokenRequest(client_id, client_secret, auth_code, refresh_request, BUFSIZE);

    if(is_verbose){
        printf( "refresh_request: %s \n", refresh_request);
    }

    bool  ret2 = getRefreshTokenToFile(refresh_request, refresh_file, error, is_verbose);
    if( !ret2 ) {
        return false;
    }

    return true;
}


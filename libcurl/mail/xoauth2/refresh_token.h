#pragma once
/**
  * refresh_token.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "client_credentials.h"
#include "redirect_url.h"
#include "request_token.h"
#include "config.h"


// prototype
void  buildRefreshTokenRequest(char * auth_code, char * request);
void  build_refresh_token_request(char * client_id, char * client_secret, char * auth_code, char* redirect_uri, char * request);


/**
 *  buildRefreshTokenRequest
 */
void  buildRefreshTokenRequest(char * auth_code, char * request)
{
    const size_t BUFSIZE = 128;
    char client_id[BUFSIZE];
    char client_secret[BUFSIZE];
   char redirect_uri[BUFSIZE];
    char error[BUFSIZE];

    bool ret1 = read_client_credentials(
(char *)client_id, (char *)client_secret, (char *)error );
    if(!ret1){
        fprintf(stderr, "cannot read client_credentials: %s \n", error);
    }

    getRedirectUri( (char *)redirect_uri );

    build_refresh_token_request( 
(char * )client_id, (char * )client_secret, auth_code, (char *) redirect_uri, request);

}


/**
 *  build_refresh_token_request
 */
void  build_refresh_token_request(char * client_id, char * client_secret, char * auth_code, char* redirect_uri, char * request)
{
// feedbackOAuth 2.0 for Mobile & Desktop Apps
// https://developers.google.com/identity/protocols/oauth2/native-app?hl=en


// https://developers.google.com/identity/protocols/oauth2/native-app#step-2:-send-a-request-to-googles-oauth-2.0-server

//、https://oauth2.googleapis.com/token 

const char FORMAT[] =
"grant_type=authorization_code&client_id=%s&client_secret=%s&code=%s&redirect_uri=%s";

    const size_t BUFSIZE = 512;
    char buf[BUFSIZE];

    snprintf( (char *)buf, BUFSIZE, (char *)FORMAT, 
client_id,  client_secret, auth_code, redirect_uri);

    strcpy(request, buf);
}


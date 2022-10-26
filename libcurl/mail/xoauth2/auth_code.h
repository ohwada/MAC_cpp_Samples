#pragma once
/**
  * auth_code.h
 * 2022-06-01 K.OHWADA
 */

#include <stdlib.h>
#include <string.h>
#include "client_credentials.h"
#include "redirect_url.h"


bool pleaseEnterAuthorizationCode();
void please_enter_auth_code(char * auth_url);
bool getAuthorizationCodeUrl(char * code_url);
void build_auth_code_url(char* scope, char * client_id, int port, char * code_url);



const char SCOPE_MAIL[] = "https://mail.google.com/";

const char SCOPE_READONLY[] = 
"https://www.googleapis.com/auth/gmail.readonly";

const char SCOPE_SEND[] = 
"https://www.googleapis.com/auth/gmail.send";


/**
 * getAuthorizationCodeUrl
 */
bool getAuthorizationCodeUrl(char * code_url)
{
    const size_t BUFSIZE = 128;
    char client_id[BUFSIZE];
    char client_secret[BUFSIZE];
    char error[BUFSIZE];

    bool ret = read_client_credentials(
(char *)client_id, (char *)client_secret, (char *)error );
    if(!ret){
        fprintf(stderr, "cannot read_client_credentials: %s \n", error);
        return false;
    }

    build_auth_code_url( 
(char *)SCOPE_MAIL, (char *) client_id, PORT, code_url);

    return true;
}


/**
 * build_auth_code_url
 */
void build_auth_code_url(char* scope, char * client_id, int port, char * code_url)
{
// Out-Of-Band (OOB) flow Migration Guide
// https://developers.google.com/identity/protocols/oauth2/resources/oob-migration?hl=en

    const char URL[] = 
"https://accounts.google.com/o/oauth2/auth";

    const char FORMAT[] =
"%s?response_type=code&scope=%s&client_id=%s&redirect_uri=%s&ack_oob_shutdown=2022-08-31";

    const size_t BUFSIZE = 512;
   char redirect_uri[BUFSIZE];
    char buf[BUFSIZE];
    
    getRedirectUri( (char *)redirect_uri );

    snprintf((char *)buf, BUFSIZE, (char *)FORMAT, 
URL, scope, client_id, (char *)redirect_uri);

    strcpy(code_url, buf);
}


/**
 * pleaseEnterAuthorizationCode
 */
bool pleaseEnterAuthorizationCode()
{
    const size_t BUFSIZE = 512;
    char code_url[BUFSIZE];

    bool ret = getAuthorizationCodeUrl( (char *)code_url );
    if(!ret){
        return false;
    }

    please_enter_auth_code( (char *)code_url );

    return true;
}


/**
 * please_enter_auth_code
 */
void please_enter_auth_code(char * auth_url)
{
    printf("\n Please Enter the following URL into Web Browser: \n");
    printf("%s \n", auth_url);
}



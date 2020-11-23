/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// send mail with Google API

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "gmail_api_request.h"
#include "access_token.h"
#include "msg_send.h"
#include "mail_json.h"



/**
 * main
 */
int main(void)
{
    const char SUBJECT[] = "Gmail API send";

    const char SEND_URL[] = "https://www.googleapis.com/gmail/v1/users/me/messages/send";

    const char FILE_REFRESH[] = "refresh_token_send.json";

    const char FILE_SAVE[] = "mail_send.eml";
   bool is_save = true;

    struct CurlMemory mem;

    struct MailParam  p = getGmailParam();
    printMailParam( p );
    char * FROM = p.from;
    char * TO =  p.to;




    const size_t MSG_SIZE = 10000; // 10KB
    char msg[MSG_SIZE]; 
    buildMessage( (char *)SUBJECT, FROM, TO, msg);

    printMessage(msg);

    const size_t REQ_SIZE = 10000; // 10KB
    char request[REQ_SIZE];
    build_send_request_json(msg, request, REQ_SIZE);


    printMessage(request);

    if(is_save){
        saveMessage( (char *)FILE_SAVE, msg);
    }

    char access_token[200];
    char error[100];
    bool is_verbose1 = false;
    bool is_access_save = true;

    bool ret1 = getNewAccessToken( 
    ( char *)SCOPE_SEND, 
    (char *)FILE_REFRESH,
    access_token, 
    (char *)error,
    is_access_save, is_verbose1);

    if( !ret1 ){
printf("getNewAccessToken: %s \n", error );
               return EXIT_FAILURE;
    }

    printf( "access_token: %s \n", access_token);

    char response[1000];
    bool is_verbose2 = true;

    bool ret2 = api_send_request( request, access_token, 
    (char *)response, 
    (char *)error, 
    is_verbose2);

    int exit;
    if( ret2 ){
            printResponse(response);
            exit = EXIT_SUCCESS;
    } else{
            printf("api_send_request: %s, \n", error );
            exit = EXIT_FAILURE;
    }

       return exit;
}

// Connected to www.googleapis.com
//  "id": "175db8ff3dcad",


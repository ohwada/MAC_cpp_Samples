/**
 * GMail API Sample
 * 2020-07-01 K.OHWADA
 */

// get message list and first one message with Google API

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gmail_api_request.h"
#include "access_token.h"
#include "response_json.h"
#include "char_array.h"


/**
 * main
 */
int main(void)
{

    char FILE_LIST_RESPONSE[] = "list_response.json";

    const char FILE_REFRESH[] = "refresh_token_readonly.json";

    char access_token[200];
    char error[100];
    bool is_access_save = true;
    bool is_verbose1 = false;

    bool ret1 = getNewAccessToken( 
    ( char *)SCOPE_READONLY, 
    (char *)FILE_REFRESH,
    access_token, 
    (char *)error,
    is_access_save, is_verbose1);

    if( !ret1 ){
        printf( "getNewAccessToken: %s \n", error);
        return EXIT_FAILURE;
    }

    printf( "access_token: %s \n", access_token);

// get message list

    bool is_verbose2 = true;

    bool ret3 = api_list_request_to_file( access_token, 
    (char *)FILE_LIST_RESPONSE, 
    (char *)error,
    is_verbose2 );
   
    if( !ret3 ){
        printf("api_list_request_to_file: %s \n",error );
        return EXIT_FAILURE;
    }



// get id list
    const int IDS_SIZE = 10;
    const int ID_LENGTH = 100;

    char** ids = alloc_chars(IDS_SIZE , ID_LENGTH ); 

    int mail_num;
    bool is_verbose3 = false;

    bool ret4 = readListResponseJsonFile( (char *)FILE_LIST_RESPONSE, ids, IDS_SIZE , &mail_num, error, is_verbose3); 

    if( !ret4 ){
        printf("readListResponseJsonFile: %s \n", error);
        free_chars(ids, IDS_SIZE ); 
        return EXIT_FAILURE;
    }

   printf("You have %d mails \n", mail_num);
    print_chars(ids, IDS_SIZE);

// get first one message

    const size_t BUFSIZE = 100;
    char url[BUFSIZE];
    char msg_file[BUFSIZE];

    char id[100];
    strcpy(id, ids[0]);

    free_chars(ids, IDS_SIZE ); 

    snprintf(url, BUFSIZE, "%s/%s", URL_API_MESSAGES, id);
    printf("url: %s \n", url);

    snprintf(msg_file, BUFSIZE, "msg_%s.json", id);
    printf("msg file: %s \n", msg_file);

    bool is_verbose4 = true;

    bool ret5= api_msg_request_to_file( id, 
    access_token, 
    (char* )msg_file, 
    (char *)error, 
    is_verbose4);

    if( !ret5 ){
        printf("api_msg_request_to_file: %s \n", error);
        return EXIT_FAILURE;;
    }

    char msg_id[100];
    char subject[100];
    char from[100];
    char date[100];
    char snippet[500];
    bool is_verbose5 = false;

    int ret6 = readMessageResponseJsonFile( 
    msg_file, 
    msg_id, subject, from, date, snippet,
    error, is_verbose5) ;

    if( !ret6 ){
                printf("readMessageResponseJsonFile: %s \n", error);
                return EXIT_FAILURE;
    }

    printf("\n");
    printf("msg id: %s \n", msg_id);
    printf("subject: %s \n", subject);
    printf("from: %s \n", from);
    printf("date: %s \n", date);
    printf("snippet: %s \n", snippet);

       return EXIT_SUCCESS;
}


// Connected to www.googleapis.com
// saved to: list_response.json 
// saved to: msg_1753fc0c1147.json 
// msg id: 1753fc0c1147
// subject: foobar


/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail using Google API

// g++ src/send_mail_text.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o text  

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include "send_mail.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    const string SUBJECT("gmail api cpp send");

    const string SEND_URL( 
    "https://www.googleapis.com/gmail/v1/users/me/messages/send");

    const string REFRESH_FILE("refresh_token_send.json");

    struct MailParam  p = getGmailParam();
    printMailParam( p );
    string FROM = p.from;
    string TO =  p.to;


    string body;
    buildDefaultBody(body);

    string msg;
    buildMessageText(SUBJECT, TO, FROM, body, msg );


    printMessage( msg ); 


    string request;
    buildSendRequestJson(msg, request);

    printMessage( request );

    bool is_save = true;
    if(is_save){
        saveMessage(msg);
    }


    string access_token;
    string error;
    bool is_verbose_access = false;
    bool is_access_save = true;

    bool ret1 = getNewAccessToken( SCOPE_SEND, 
    REFRESH_FILE,
    access_token, 
    error,
    is_access_save, is_verbose_access);

    if(ret1){
        cout << "access_token: " << access_token << endl;
    } else {
        cout << "getNewAccessToken: " << error << endl;
        return EXIT_FAILURE;
    }


    string response;
    bool is_verbose_send = true;

   bool ret2 = api_send_request( request,   access_token, response,  error, is_verbose_send);

    if(ret2 ){
        printResponse( response );
    } else {
            cout << "api_send_request: " << error  << endl;
            return EXIT_FAILURE;
    }
 
    cout << "send mail sucessful"<< endl;
    return EXIT_SUCCESS;
}


// Connected to www.googleapis.com
// "id": "17543ff565db"




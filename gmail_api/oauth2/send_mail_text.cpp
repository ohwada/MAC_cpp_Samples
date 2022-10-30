/**
 * send_mail_text.cpp
 * 2022-06-01 K.OHWADA
 */

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include "oauth_request_sender.hpp"
#include "msg_builder_gmail.hpp"
#include "msg_builder.hpp"
#include "json_mail.hpp"
#include "gmail_api_request.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const string SUBJECT("gmail api send");

    struct MailParam  p = getGmailParam();
    printMailParam( p );
    string FROM = p.from;
    string TO =  p.to;


    string body = 
    getDefaultBody();

    string msg = 
    buildMessageText(SUBJECT, TO, FROM, body);

    printMessage( msg ); 

    saveMessage(msg);


    string request =
    buildRequestMailSendJson(msg);

    saveRequestJson(request);
 

    string access_token;
    string error;
    bool is_verbose_token = false;

    bool ret1 = getNewAccessToken( 
    access_token, error, is_verbose_token );

    if(!ret1){
        cout << "getNewAccessToken: " << error << endl;
        return EXIT_FAILURE;
    }

    printAccessToken(access_token);

    string response;
    bool is_verbose_send = true;

   bool ret2 = api_mail_send( request,  access_token, response,  error, is_verbose_send);

    if(!ret2 ){
            cout << "api_mail_send: " << error  << endl;
            return EXIT_FAILURE;
    }
 
    printResponse( response );

    cout << "send mail sucessful"<< endl;

    return EXIT_SUCCESS;
}


// Connected to www.googleapis.com
// "id": "17543ff565db"



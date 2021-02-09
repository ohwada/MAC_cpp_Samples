/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail with using UTF-8 encoding Google API

// g++ src/send_mail_utf8.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o utf8 

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


#include <iostream>
#include "send_mail.hpp"
#include "msg_builder_charset.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    const string SEND_URL( 
    "https://www.googleapis.com/gmail/v1/users/me/messages/send");

    const string REFRESH_FILE("refresh_token_send.json");

    struct MailParam  p = getGmailParam();
    printMailParam( p );
    string FROM = p.from;
    string TO =  p.to;

    const std::string SUBJECT("gmail api utf8 テスト");

    const std::string CHARSET("UTF_8");

// body
    string body("これはテストメールです \n");

    body += std::string("このメールの文字コードは UTF-8 です \n");
    body += std::string("このメールは Gmail API を使って送信されました \n");

    string msg;
    buildMessageUtf8( SUBJECT, TO, FROM,  body,  msg );


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
    bool verbose1 = false;
    bool is_access_save = true;

    bool ret1 = getNewAccessToken( SCOPE_SEND, 
    REFRESH_FILE,
    access_token, 
    error,
    is_access_save, verbose1);

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




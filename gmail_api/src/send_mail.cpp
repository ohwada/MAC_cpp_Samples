/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail using Google API

// g++ src/send_mail.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o send  

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include <string>
#include "gmail_api_request.hpp"
#include "access_token.hpp"
#include "mail_json.hpp"
#include "msg_build.hpp"


// prototype
void buildMessageCpp(std::string str_subject, std::string str_from, std::string str_to, std::string &ret_msg);
void build_send_request(char* msg,std::string request, size_t size);
void printRequrst(std::string request);


/**
 * buildMessage
 * RFC 2822 format
 */
void buildMessageCpp(std::string str_subject, std::string str_from, std::string str_to, std::string &ret_msg)
{
    char* subject = (char *)str_subject.c_str();
    char* from =  (char *)str_from.c_str();
    char* to =  (char *)str_to.c_str();

    const size_t MSG_SIZE = 10000; // 10KB
    char msg[MSG_SIZE];

    buildMessage( subject, from, to, msg);

    ret_msg= msg;
}


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


    string msg;
    buildMessageCpp( SUBJECT, FROM, TO, msg);

    printRequrst( msg ); 


    string request;
    buildSendRequestJson(msg, request);

    printRequrst( request );

    bool is_save = false;
    if(is_save){
        saveMessage(msg);
    }

   // return 1;


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




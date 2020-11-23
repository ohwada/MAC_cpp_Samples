/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail with attached file using Google API

// g++ src/send_mail_attach.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o attach 

// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send


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



using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string SUBJECT("gmail api attach");

    const string SEND_URL( 
    "https://www.googleapis.com/gmail/v1/users/me/messages/send");

    const string REFRESH_FILE("refresh_token_send.json");

    string file = "data/baboon.png";
    bool is_save = true;

   if(argc == 3){
        file =   argv[1] ;
        is_save =  (bool)stoi( argv[2] );
   } else if (argc == 2) {
        file =   argv[1] ;
    } else {
        cout << "usage: " << argv[0] << " [file ][save] " << endl;
    }


    struct MailParam  p = getGmailParam();
    printMailParam( p );
    string FROM = p.from;
    string TO =  p.to;

// body
    std::string body("This is test email. \r\n");
    body += string("this mail has one attached file. \r\n");
    body += string("this mail sent using Gmail API. \r\n");


    string msg;
    bool ret1 = buildMessageAttachment( 
    SUBJECT, FROM, TO, 
    body,  file, msg);

if(!ret1){
    return EXIT_FAILURE;
}

    printRequrst( msg ); 


    string request;
    buildSendRequestJson(msg, request);

    printRequrst( request );

    if(is_save){
        saveMessage(msg);
    }

    //return 1;


    string access_token;
    string error;
    bool verbose_access = false;
    bool is_access_save = true;

    bool ret2 = getNewAccessToken( SCOPE_SEND, 
    REFRESH_FILE,
    access_token, 
    error,
    is_access_save, verbose_access);

    if(ret2){
        cout << "access_token: " << access_token << endl;
    } else {
        cout << "getNewAccessToken: " << error << endl;
        return EXIT_FAILURE;
    }


    cout << "access_token: " << access_token << endl;


    string response;
    bool is_verbose_send = true;

   bool ret3 = api_send_request( request,   access_token, response,  error, is_verbose_send);

    if(ret3 ){
        printResponse( response );
    } else {
            cout << "api_send_request: " << error  << endl;
            return EXIT_FAILURE;
    }


    cout << "send mail sucessful"<< endl;
    return EXIT_SUCCESS;
}



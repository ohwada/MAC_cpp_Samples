/**
 * Gmail API sample
 * 2020-07-01 K.OHWADA
 */

// send mail using Google API
// mail with attached text file


// TODO:
// upload large image
// can upload 256x265 size (39KB)
// can not upload 512x512 size (164KB)



// g++ src/send_mail_attach.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o attach 


// https://developers.google.com/gmail/api/reference/rest/v1/users.messages/send
// https://developers.google.com/gmail/api/guides/uploads


#include <iostream>
#include "send_mail.hpp"
#include "msg_builder_attach.hpp"


/**
 * saveRequest
 */
bool saveRequest( std::string request )
{
    std::string prefix("request");
    std::string ext("txt");
    std::string filename;
    getTimestampFileName( prefix, ext, filename );

    bool ret =  writeTextFile( filename,  request );

    if(ret){
        std::cout << "saved to: " << filename << std::endl;
    } else {
        std::cerr << "writeTextFile failed: " << filename << std::endl;
    }

    return ret;
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string SUBJECT("gmail api attach");

    const string SEND_URL( 
    "https://www.googleapis.comgmail/v1/users/me/messages/send");

    const string REFRESH_FILE("refresh_token_send.json");

// TODO:
// upload large image
    string file = "data/baboon256.jpg";


   if (argc == 2) {
        file =   argv[1] ;
    } else {
        cout << "usage: " << argv[0] << " [file] " << endl;
    }


    struct MailParam  p = getGmailParam();
    printMailParam( p );
    string FROM = p.from;
    string TO =  p.to;

// body
    std::string body("This is test email.");
    body += CRLF;
    body += string("this mail has one attached text file.");
    body += CRLF;
    body += string("this mail sent using Gmail API.");
    body += CRLF;

    string msg;
    string error;
    bool ret1 = buildMessageAttachment( 
    SUBJECT, FROM, TO, 
    body,  file, msg, error );

if(!ret1){
    cerr << error << endl;
    return EXIT_FAILURE;
}

    // printMessage( msg ); 

    bool is_save = true;
    if(is_save){
        saveMessage(msg);
    }


    string request;
    buildSendRequestJson(msg, request);

    // printMessage( request );

    bool is_save_request = true;
    if(is_save_request) {
        saveRequest(request);
    }

    string access_token;
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



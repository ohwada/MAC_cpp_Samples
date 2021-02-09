/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with ISO-2022JP encoding

// require libiconv 
 // g++ src/create_mail_iso2022jp.cpp  -std=c++11  `pkg-config --cflags --libs iconv` 


#include <iostream>
#include "msg_builder_charset.hpp"
#include "iso2022jp.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const string subject("iso2022jp テスト");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

// body
    std::string body("これはテストメールです。 ");
    body += CRLF;
    body += string("このメールの文字コードは ISO-2022-JP です。 ");
    body += CRLF;

    
    string subject_iso2022;
    string body_iso2022;
    string error;

    bool ret1 = convToIso2022jp( subject,  subject_iso2022,  error );
    if( !ret1){
        cerr << error << endl;
        return EXIT_FAILURE;
    }

    bool ret2 = convToIso2022jp( body,  body_iso2022,  error );
    if( !ret2){
        cerr << error << endl;
        return EXIT_FAILURE;
    }


    string msg;
    buildMessageCharset( subject_iso2022, TO, FROM, body_iso2022, CHARSET_ISO2022JP, msg );

    printMessage(msg);
    saveMessage(msg);

    return EXIT_SUCCESS;
}



/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with UTF-8 encoding

 // g++ src/create_mail_utf8.cpp  -std=c++11


#include <iostream>
#include "msg_builder.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    const string SUBJECT("utf8 テスト");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

// body
    std::string body("これはテストメールです。 \r\n");
    body += string("このメールの文字コードは UTF-8 です。 \r\n");

    string msg;
    buildMessageUtf8( SUBJECT, TO, FROM, body, msg);

    printMessage(msg);
    saveMessage(msg);

    return EXIT_SUCCESS;
}



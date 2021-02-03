/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create simple text mail 

// g++ src/create_mail_text.cpp -std=c++11 



#include <iostream>
#include <string>
#include "msg_builder.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    const string SUBJECT("mail text");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

// body
    std::string body("This is test email. \r\n");
    body += string("this mail has simple plane text. \r\n");

    string msg;
    buildMessageText( SUBJECT, TO, FROM, body, msg);

    printMessage(msg);
    saveMessage(msg);

    return EXIT_SUCCESS;
}



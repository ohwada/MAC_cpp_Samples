/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with HTML 

// g++ src/create_mail_html.cpp -std=c++11 



#include <iostream>
#include "msg_builder_html.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    const string SUBJECT("mail html");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

// plain
    std::string plain("This is test email. ");
    plain += CRLF;
    plain += string("this mail has html. ");
    plain += CRLF;
    plain += string("this part is plain text. ");
    plain += CRLF;


// html
    std::string html("This is test email. <br/>");
    html += CRLF;
    html += string("this mail has <b>html</b>. <br/>");
    html += CRLF;
    html += string("this part is <b>html</b>. <br/>");
    html += CRLF;

    string msg;
    buildMessageHtml( SUBJECT, TO, FROM, plain,  html, msg );

    printMessage(msg);
    saveMessage(msg);

    return EXIT_SUCCESS;
}



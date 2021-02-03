/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with HTML and attached file

// g++ src/create_mail_html_attach.cpp -std=c++11 



#include <iostream>
#include "msg_builder_html.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string SUBJECT("mail html attach");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

    string filepath = "data/milkcrown.jpg";

   if (argc == 2) {
        filepath =   argv[1] ;
    } else {
        cout << "usage: " << argv[0] << " [file ] " << endl;
    }

    cout << filepath << endl;

// plain
    std::string plain("This is test email.");
    plain += CRLF;
    plain += string("this mail has html and attached file.");
    plain += CRLF;
    plain += string("this part is plain text.");
    plain += CRLF;

    cout << plain << endl;

// html
    std::string html("This is test email. <br/>");
    html += CRLF;
    html += string("this mail has <b>attached file</b>. <br/>");
    html += CRLF;
    html += string("this part is <b>html</b>. <br/>");
    html += CRLF;
    cout << html << endl;

    string msg;
    string error;

    bool ret = buildMessageHtmlAttachment( SUBJECT, TO, FROM, plain,  html, filepath, msg, error );
    
    if(!ret){
        cerr << error << endl;
        return EXIT_FAILURE;
    }

    saveMessage(msg);

    return EXIT_SUCCESS;
}



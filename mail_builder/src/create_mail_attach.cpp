/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with attached file

// g++ src/create_mail_attach.cpp -std=c++11 


#include <iostream>
#include "msg_builder_attach.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string SUBJECT("mail attach");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

    string file = "data/baboon.jpg";

   if (argc == 2) {
        file =   argv[1] ;
    } else {
        cout << "usage: " << argv[0] << " [file ] " << endl;
    }

// body
    std::string body("This is test email. \r\n");
    body += string("this mail has one attached file. \r\n");

    string msg;
    string error;
    bool ret = buildMessageAttachment( 
    SUBJECT, FROM, TO, 
    body,  file, msg, error );

    if(!ret ){
        cerr << error << endl;
        return EXIT_FAILURE;
    }

        saveMessage(msg);

    return EXIT_SUCCESS;
}



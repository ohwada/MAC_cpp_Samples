/**
 * mail builder
 * 2021-02-01 K.OHWADA
 */

// create mail with Two attached file

// g++ src/create_mail_attach_two.cpp -std=c++11 


#include <iostream>
#include "msg_builder.hpp"

// prototype
bool buildMessageAttachmentTwo( std::string str_subject, std::string str_to, std::string str_from, std::string body,  std::string filepath1, std::string filepath2, std::string &ret_msg, std::string &ret_error );




/**
 *  buildMessageAttachmentTwo
 */
bool buildMessageAttachmentTwo( std::string str_subject, std::string str_to, std::string str_from, std::string body,  std::string filepath1, std::string filepath2, std::string &msg, std::string &ret_error )
{

    std::string attach1;
    std::string error;

    bool ret1 = buildAttachment( filepath1,  attach1, error );

    if(!ret1){
        ret_error = error;
        return false;
    }

    std::string attach2;

    bool ret2 = buildAttachment( filepath2,  attach2, error );

    if(!ret2){
        ret_error = error;
        return false;
    }


	// boundary
    std::string boundary;
    getBoundary( boundary );

    std::string content_type_multipart;
    std::string boundary_begin;
    std::string boundary_end;
    getContentTypeMultipartMixed( boundary,  content_type_multipart,  boundary_begin, boundary_end );


    std::string headers;
    buildHeaders(str_subject, str_to, str_from,  headers);


// build msg
    msg = headers;

// text
    msg += content_type_multipart;
    msg += CRLF;
    msg += boundary_begin;
    msg += CONTENT_TYPE_TEXT_PLANE_USASCII;
    msg += CONTENT_TRANSFER_7BIT;

		msg += CRLF; // saparator

        msg += body + CRLF;


// attachment
    msg += boundary_begin;
    msg += attach1;
msg += CRLF;

    msg += boundary_begin;
    msg += attach2;
msg += CRLF;
    
    msg +=  boundary_end;

    return true;

}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string SUBJECT("mail attach");

    const string TO("taro@example.com");

    const string FROM("jiro@example.com");

    string file1 = "data/vegetables.jpg";
    string file2 = "data/text_utf8.txt";

   if (argc == 3) {
        file1 =   argv[1] ;
        file2 =   argv[2] ;
    } else {
        cout << "usage: " << argv[0] << " [file1] [file2] " << endl;
    }

// body
    std::string body("This is test email. \r\n");
    body += string("this mail has two attached file. \r\n");

    string msg;
    string error;
    bool ret1 = buildMessageAttachmentTwo( 
    SUBJECT, FROM, TO, 
    body,  file1, file2, msg, error );

    if(ret1){
        // printMessage(msg);
        saveMessage(msg);
    } else {
        cerr << error << endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}



/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// mail with plane text body
// support Non-ASCII encoding like UTF-8, ISO2022JP


// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/19/105757


#include <iostream>
#include "msg_read.hpp"
#include "vmime_header.hpp"
#include "vmime_body.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

string filepath("samples/mail_text.eml");

    if (argc == 2) {
      	filepath = argv[1];
    } else {
     cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

  
    std::string error;
    vmime::shared_ptr <vmime::message> msg =
    readMailFile(filepath, error);

    if( msg ){
        cout << "readMailFile: " << filepath  << endl;
    } else {
        cerr << error  << endl;
        return EXIT_FAILURE;;
    }

// header
    vmime::shared_ptr <vmime::header> hdr = msg->getHeader();

    struct HeaderInfo header_info;

    getHeaderInfo( hdr, header_info );

    printHeaderInfo( header_info );


// body
    vmime::shared_ptr<vmime::body> body = msg->getBody();

    struct Bodyinfo body_info;

    getBodyInfo(body, body_info );

    auto body_label = body_info.label;

    std::string content;

    getTextBody( body, content );

    cout << body_label << endl;
    cout << content << endl;
 
    return EXIT_SUCCESS;
}




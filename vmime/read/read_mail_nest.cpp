/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// emails with complex structures
// nested multipart 
// iso-2022jp encoding

// g++ read/read_mail_nested.cpp -std=c++11 `pkg-config --cflags --libs vmime` 

#include <iostream>
#include "msg_read.hpp"
#include "vmime_body_part.hpp"
#include "html_write.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{


string filepath("data/sample_nest.eml");

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

    struct HeaderInfo hdr_info;

    getHeaderInfo( hdr, hdr_info );

    printHeaderInfo( hdr_info );

    vmime::shared_ptr<vmime::body> body = msg->getBody();

    size_t 	count = body->getPartCount();
    cout << "part count: " << count << endl;
    cout << endl;

    std::string content;
    std::string info;

    if(count == 0){
        getTextBody( body, content );
        cout << content << endl;
        return EXIT_SUCCESS;
    }


    std::string plain;
    std::string html;

    int depth = 0;
    bool is_debug = true;

    bool ret = getTextBodyRecursive( depth, body, plain, html,  is_debug);

    if(ret){
        if(plain.length() > 0){
            printContent(plain);
        }
    } else {
        cout << "can not find text boy" <<  endl;
    }

    if(html.length() > 0) {

        cout << "this mail has html" << endl;
        procHtmlMenu( html );

    } // if html

    return EXIT_SUCCESS;
}


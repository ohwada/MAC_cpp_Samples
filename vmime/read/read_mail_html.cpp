/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// mail with attached file 

// g++ read/read_mail_html.cpp -std=c++11 `pkg-config --cflags --libs vmime`

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

    const std::string COLON(" : "); 
    const std::string STAR(" * "); 
   const std::string EMPTY("   "); 

    string filepath("result/mail_html.eml");

    if (argc == 2) {
      	filepath = argv[1];
    } else {
     cout << "Usage: " << argv[0] << " [file] "  << endl;
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

 vmime::shared_ptr <vmime::body> body = msg->getBody();

    size_t 	count = body->getPartCount();
    if(count == 0){
        return EXIT_SUCCESS;
    }

cout << endl;
 cout << "this mail has " << count << " body parts " << endl;
cout << endl;

    struct Bodyinfo part_body_info;
    std::string part_type;
    // std::string  part_label;
    std::string  part_text_info;
    std::string  part_content;
    std::string  part_disposition;

    std::string  plain_content;
    std::string  html_content;

 
    struct BodyPartInfo body_part_info;


for(int i=0; i<count; i++){

        vmime::shared_ptr<vmime::bodyPart> part =  body->getPartAt(i);

        vmime::shared_ptr< vmime::body > 	part_body = part->getBody();

        getBodyPartInfo( part,  body_part_info);

        bool is_inline_text  =body_part_info.is_inline_text;

     bool is_inline_text_plain  =body_part_info.is_inline_text_plain;

     bool is_inline_text_html  =body_part_info.is_inline_text_html;

        std:;string part_label  =body_part_info.label;

        std::string part_mark = EMPTY;

        if(is_inline_text){
                part_mark = STAR;
        }

        cout << i <<  COLON << part_mark << part_label << endl;

   if(is_inline_text_plain){
                getTextBody( part_body, part_content );
                plain_content =part_content;
        }

   if(is_inline_text_html){
                getTextBody( part_body, part_content );
                html_content =part_content;
        }

} // for

        cout << endl;
        cout << "plain ---------" << endl;
                cout << plain_content << endl;
        cout << "---------" << endl;
       cout << endl;

    if( html_content.length() > 0 ) {

        cout << "this mail has html" << endl;
        procHtmlMenu( html_content );

    } // if html

    return EXIT_SUCCESS;
}


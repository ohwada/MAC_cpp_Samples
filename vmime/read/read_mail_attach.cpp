/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// mail with attached file 

// g++ read/read_mail_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime`

// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/20/143235

#include <iostream>
#include "msg_read.hpp"
#include "vmime_body_part.hpp"
#include "vmime_attachment_util.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    const std::string COLON(" : "); 
    const std::string STAR(" * "); 
   const std::string EMPTY("   "); 

    string filepath("result/mail_attach.eml");

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
    std::string  content;


 
    struct BodyPartInfo body_part_info;


for(int i=0; i<count; i++){

        vmime::shared_ptr<vmime::bodyPart> part =  body->getPartAt(i);

        vmime::shared_ptr< vmime::body > 	part_body = part->getBody();

        getBodyPartInfo( part,  body_part_info);

        bool is_inline_text  =body_part_info.is_inline_text;

        std:;string part_label  =body_part_info.label;

        std::string part_mark = EMPTY;

        if(is_inline_text){
                getTextBody( part_body, part_content );
                content =part_content;
                part_mark = STAR;
        }

        cout << i <<  COLON << part_mark << part_label << endl;

} // for

        cout << endl;
        cout << "---------" << endl;
                cout << content << endl;
        cout << "---------" << endl;
       cout << endl;


// attachment
    std::vector< vmime::shared_ptr< const vmime::attachment > > atts;

    bool is_debug = true;
    getAttachments( msg, atts, is_debug );

    size_t att_size = atts.size();

    if( att_size == 0 ){
        return EXIT_SUCCESS;
    }

    cout << endl;
    cout << "this mail has " << att_size << " attachments " << endl;
    cout << endl;

    procAttachmentMenu( atts );

    return EXIT_SUCCESS;
}


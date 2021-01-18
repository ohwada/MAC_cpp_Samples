/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// mail with attached file 

// g++ read/read_mail_embed.cpp -std=c++11 `pkg-config --cflags --libs vmime`


 // original : https://github.com/kisli/vmime/blob/master/examples/example3.cpp

// This sample program demonstrate the use of the messageBuilder component
// to build a complex message (HTML content, plain text and embedded image).


#include <iostream>
#include "msg_read.hpp"
#include "vmime_body_part.hpp"
#include "html_write.hpp"

// constant
const std::string PREFIX("embed_");


// prototype
void getEmbedHtml( vmime::shared_ptr<vmime::bodyPart> bodypart,  std::string &html_content );

bool replaceEmbedHtml( std::string html_content, std::string content_id, std::string image_filename, std::string  &replaced );

bool savEmbedHtml( std::string html_replaced,  std::string timestamp,  std::string &ret_html_filename );

bool  getEmbedImageContentId( vmime::shared_ptr<vmime::bodyPart> bodypart, std::string &content_id );

bool saveEmbedImage( vmime::shared_ptr<vmime::bodyPart> bodypart, struct BodyPartInfo body_part_info, std::string timestamp,  std::string &ret_image_filename );

bool procEmbed( vmime::shared_ptr<vmime::bodyPart> bodypart,  struct BodyPartInfo body_part_info, std::string &html_content );

bool replaceString(std::string src, std::string s1,  std::string s2, std::string &dst);




/**
 *  getEmbedHtml
 */
void getEmbedHtml( vmime::shared_ptr<vmime::bodyPart> bodypart,  std::string &html_content )
{

    vmime::shared_ptr< vmime::body > 	part_body = bodypart->getBody();

    std::string part_content;
    getTextBody( part_body, part_content );
    html_content = part_content;
}


/**
 *  replaceEmbedHtml
 */
bool replaceEmbedHtml( std::string html_content, std::string content_id, std::string image_filename, std::string  &replaced )
{

   std::string  target = "cid:" + content_id;

bool ret1 = replaceString( html_content, target,  image_filename, replaced);

    if(!ret1){
        std::cerr << "replaceString failed " << std::endl;
        return false;
    }

    return true;
}


/**
 *  getEmbedImageContentId
 */
bool  getEmbedImageContentId( vmime::shared_ptr<vmime::bodyPart> bodypart,  std::string &content_id )
{

       vmime::shared_ptr< vmime::header > 	part_hdr = bodypart->getHeader();

        vmime::shared_ptr< vmime::body > 	part_body = bodypart->getBody();

        bool  ret = getContentId( part_hdr,  content_id );
        if(!ret){
                std::cerr << "can not get ContentId" << std::endl;
                return false;
        }

    return true;
}



/**
 *  savEmbedHtml
 */
bool savEmbedHtml( std::string html_replaced,  std::string timestamp,  std::string &ret_html_filename )
{

    std::string html_filename = PREFIX + timestamp +".html";

    bool ret = writeTextFile( html_filename, html_replaced );
 
    if(!ret){
        std::cerr <<  " writeTextFile faild: " << html_filename << std::endl;
        return false;
    }

    ret_html_filename = html_filename;

    return true;
}


/**
 *  saveEmbedImage
 */
bool saveEmbedImage( vmime::shared_ptr<vmime::bodyPart> bodypart, struct BodyPartInfo body_part_info, std::string timestamp,  std::string &ret_image_filename )
{

    const std::string DOT("."); 

    std::string subtype = body_part_info.subtype;

        std::string image_filename =  PREFIX + timestamp + DOT + subtype;
        ret_image_filename = image_filename;

        vmime::shared_ptr< vmime::body > 	part_body = bodypart->getBody();

        bool ret = saveBody( part_body,  image_filename );
        if(!ret){
               std::cout << "saveBody faild: " << image_filename << std::endl;
                return false;
        }

    return true;
}



/**
 * replaceString
 */
bool replaceString(std::string src, std::string s1,  std::string s2, std::string &dst)
{

    std::string::size_type pos = src.find(s1);

    if (pos == std::string::npos) {
        dst = "";
        return  false;
    }
    
    dst = src;
    dst.replace(pos, s1.length(),  s2);
    return true;
}


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    const std::string COLON(" : "); 
    const std::string STAR(" * "); 
   const std::string EMPTY("   "); 
    const std::string HYPHEN(" - "); 

    string filename("result/mail_embed.eml");

    if (argc == 2) {
      	filename = argv[1];
    } else {
     cout << "Usage: " << argv[0] << " [file] "  << endl;
    }

std::string error;
    vmime::shared_ptr <vmime::message> msg =
    readMailFile(filename, error);

    if( msg ){
        cout << "readMailFile: " << filename  << endl;
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

std::string  body_content;
std::string html_content;

for(int i=0; i<count; i++){

        vmime::shared_ptr<vmime::bodyPart> part_i =  body->getPartAt(i);

        struct BodyPartInfo body_part_info_i;
        getBodyPartInfo( part_i,  body_part_info_i);

std::string label_i = body_part_info_i.label;
cout << i << COLON << label_i << endl;

size_t part_count_i = body_part_info_i.part_count ;
bool is_inline_text_i = body_part_info_i. is_inline_text;

      vmime::shared_ptr< vmime::body > 	part_body_i = part_i->getBody();

    if (is_inline_text_i){
            std::string part_content_i;
             getTextBody( part_body_i, part_content_i );
                body_content =part_content_i;
    }

    if(part_count_i == 0){
        continue;
    }

for(int j=0; j<part_count_i; j++){

        vmime::shared_ptr<vmime::bodyPart> part_j =  body->getPartAt(j);

        vmime::shared_ptr< vmime::body > 	part_body_j = part_j->getBody();

        struct BodyPartInfo body_part_info_j;
        getBodyPartInfo( part_j,  body_part_info_j);

        bool is_inline_text_j  =body_part_info_j.is_inline_text;

        std:;string part_label_j  =body_part_info_j.label;

        size_t count_j = body_part_info_j.part_count ;

        std::string part_mark_j = EMPTY;

        if(is_inline_text_j){
std::string part_content_j;
                getTextBody( part_body_j, part_content_j );
                body_content = part_content_j;
                part_mark_j = STAR;
        }

        cout << i << HYPHEN << j <<  COLON << part_mark_j << part_label_j << endl;

if (count_j ==0 ){
    continue;
}

std::string content_id_j;
std::string  image_filename_j;

std::string  timestamp_j;
getTimestamp(timestamp_j);

for(int k=0; k<count_j; k++){

        vmime::shared_ptr<vmime::bodyPart> part_k =  part_body_j->getPartAt(k);

        struct BodyPartInfo body_part_info_k;
        getBodyPartInfo( part_k,  body_part_info_k );

        std::string label_k = body_part_info_k.label;

       std::string type_k = body_part_info_k.type;

   bool is_inline_k = body_part_info_k.is_inline;

        bool is_inline_text_html_k = body_part_info_k.is_inline_text_html;

        cout << i << HYPHEN << j <<  HYPHEN << k <<  COLON << label_k << endl;


        if(is_inline_text_html_k) {
            std::string html_content_k;
            getEmbedHtml( part_k,  html_content_k );
            html_content = html_content_k;
        }

    if ( is_inline_k && ( type_k == "image" ) ){
        std::string content_id_k;
        std::string image_filename_k;
        bool  ret_1k = getEmbedImageContentId( part_k, content_id_k );
        if(ret_1k){
            content_id_j = content_id_k;
        }

bool ret_2k = saveEmbedImage( part_k, body_part_info_k,  timestamp_j,  image_filename_k );
        if(ret_2k){
            image_filename_j = image_filename_k;
            cout << "saved: " << image_filename_j << endl;
        }
    }

} // for k

std::string  replaced_j;
bool ret_1j = replaceEmbedHtml( html_content, content_id_j, image_filename_j, replaced_j );

 std::string html_filename_j;
bool ret_2j = savEmbedHtml( replaced_j,  timestamp_j,  html_filename_j );

if(ret_2j) {
    cout << "saved: " << html_filename_j << endl;
}

} // for j

} // for i

    cout << endl;
    cout << "---------" << endl;
                cout << body_content << endl;
    cout << "---------" << endl;
    cout << endl;

    cout << endl;

    if( html_content.length() > 0 ) {

        cout << "this mail has html" << endl;
        printContentYn( html_content );
    }

    return EXIT_SUCCESS;
}


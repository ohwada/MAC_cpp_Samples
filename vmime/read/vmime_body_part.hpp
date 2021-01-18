#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for body

#include <string>
#include "vmime/vmime.hpp"
#include "vmime_header.hpp"
#include "vmime_body.hpp"


#define MAX_DEPTH 3


/**
* struct BodyPartInfo
  */
struct BodyPartInfo
{
std::string disposition;
std::string type;
std::string subtype;
std::string charset;
std::string label;
size_t part_count;
bool is_inline;
bool is_inline_text;
bool is_inline_text_plain;
bool is_inline_text_html;
};


// prototype
bool getTextBodyRecursive(int depth, vmime::shared_ptr< vmime::body > body, std::string &content, bool is_debug);
void getBodyPartInfo(vmime::shared_ptr<vmime::bodyPart> 	part,  struct BodyPartInfo &info);



/**
 *  getTextBodyRecursive
 */
bool getTextBodyRecursive(int depth, vmime::shared_ptr< vmime::body > body, std::string &plain, std::string &html, bool is_debug)
{

    const std::string SLASH(" / "); 
    const std::string COLON(" : "); 
    const std::string HYPHEN(" - "); 
    const std::string STAR(" * "); 
   const std::string EMPTY("   "); 

    if(depth >= MAX_DEPTH){
        return false;
    }

    size_t count = body->getPartCount();

     struct Bodyinfo part_body_info;
    std::string part_type;
    std::string part_label;
    std::string  part_content;
    std::string  part_plain;
    std::string  part_html;
    size_t part_count;

    struct BodyPartInfo body_part_info;

    bool has_text = false;

    for(int i=0; i<count; i++){

        vmime::shared_ptr<vmime::bodyPart> 	part =  body->getPartAt(i);

        getBodyPartInfo( part,  body_part_info );

        bool is_inline_text  =body_part_info.is_inline_text;

        bool is_inline_text_plain  =body_part_info.is_inline_text_plain;

        bool is_inline_text_html  =body_part_info.is_inline_text_html;

        std::string part_label  =body_part_info.label;

        std::string part_mark = EMPTY;

        if(is_inline_text) {
                vmime::shared_ptr< vmime::body > 	part_body = part->getBody();
                getTextBody( part_body, part_content );
                if(is_inline_text_plain) {
                    plain =part_content;
                }
                if(is_inline_text_html) {
                    html =part_content;
                }
                part_mark = STAR;
                has_text = true;
        }

        if(is_debug) {
            std::string debug_info = std::to_string(depth) + HYPHEN + std::to_string(i) + COLON  + part_mark + part_label;
            std:: cout << debug_info << std::endl;
        }

        vmime::shared_ptr< vmime::body > 	part_body = part->getBody();

        getBodyInfo( part_body,  part_body_info );

        part_type = part_body_info.type;
        part_count = part_body_info.part_count;
        part_label = part_body_info.label;

        if(part_count > 0) {
            bool ret = getTextBodyRecursive( (depth +1 ), part_body,  part_plain,  part_html, is_debug);

            if(ret){
                plain = part_plain;
                html = part_html;
                return true;
            } else {
                return false;
            }

        } // if part_count

    }// for

    return has_text;
}


/**
 *  getBodyPartInfo
 */
void getBodyPartInfo(vmime::shared_ptr<vmime::bodyPart> 	part,  struct BodyPartInfo &info)
{

    const std::string COLON(" : "); 

    vmime::shared_ptr< vmime::header > 	part_hdr = part->getHeader();

    std::string part_disposition;
    getContentDisposition(part_hdr, part_disposition);

    vmime::shared_ptr< vmime::body > 	part_body = part->getBody();

    struct Bodyinfo part_body_info;
    getBodyInfo(part_body, part_body_info );

    std::string  part_type = part_body_info.type;
    std::string  part_subtype = part_body_info.subtype;
    std::string  part_charset = part_body_info.charset;
    std::string part_label = part_body_info.label;
    size_t part_count = part_body_info.part_count;

    std::string label = part_disposition + COLON + part_label;

    bool is_inline = false;
    bool is_inline_text = false;
   bool is_inline_text_plain = false;
   bool is_inline_text_html = false;
    if( part_disposition == "inline" ) {
        is_inline = true;
        if ( part_type == "text" ) {
            is_inline_text = true;
            if( part_subtype == "plain" ) {
                is_inline_text_plain = true;
            }
            if ( part_subtype == "html" ) {
                is_inline_text_html = true;
            }
        }
    }

    info.type = part_type;
    info.type = part_type;
    info.subtype = part_subtype;
    info.charset = part_charset;
    info.label = label;
    info.part_count = part_count;
    info.is_inline = is_inline;
    info.is_inline_text = is_inline_text;
    info.is_inline_text_plain = is_inline_text_plain;
    info.is_inline_text_html = is_inline_text_html;

}

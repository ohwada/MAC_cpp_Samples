#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// get body

#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "vmime_charset.hpp"


// prototype
void getBodyContent(
vmime::shared_ptr <vmime::net::message> msg,  
std::string &content, std::string &str_media_type, std::string &str_charset );
void get_body_content_utf8( vmime::shared_ptr<vmime::body> body, std::string &content );
void get_body_media_type( vmime::shared_ptr<vmime::body> body, std::string &str_media_type, std::string &str_charset );
bool is_body_iso2022jp( std::string media_type, std::string charset );
void getContentType( vmime::shared_ptr <vmime::message> msg, std::string &type ) ;
void extractBody( vmime::shared_ptr<vmime::body> body,  
   std::string &str_body );
bool getPlaneTextInBody(std::string src,  vmime::string &plane_text );
bool isEqualNoCase(const std::string s1, const std::string s2);


/** 
 * getBodyContent
  */
void getBodyContent(
vmime::shared_ptr <vmime::net::message> msg,  
std::string &content,  std::string &ret_media_type, std::string &ret_charset )
{

// Note:
// in case of multi-part, 
// there is content in body part
// instead of body

    vmime::shared_ptr <vmime::message> parsedMsg = msg->getParsedMessage();

    vmime::shared_ptr<vmime::body> body1 = parsedMsg->getBody();

    std::string str_media_type1;
    std::string str_charset1 ;
    get_body_media_type( body1, str_media_type1, str_charset1 );

    ret_media_type = str_media_type1;
    ret_charset = str_charset1;

    bool  is_iso2022jp1 = is_body_iso2022jp( str_media_type1, str_charset1 );

    size_t 	count1 = body1->getPartCount();

    std::string str_body1;
    extractBody(body1, str_body1 );

    std::string plane_text;
    bool ret1 = getPlaneTextInBody(str_body1,  plane_text );

    if(ret1){
        content = plane_text;
    } else if(is_iso2022jp1) {
        std::string utf8;
        iso2022jp_to_utf8(str_body1, utf8);
        content = utf8;
    } else {
        content = str_body1;
    }

    if(count1 == 0) {
// single-part
        return;
    }

 // multi-part
    vmime::shared_ptr<vmime::bodyPart> 	part2 =  
    body1->getPartAt(0);

    vmime::shared_ptr<vmime::body> body2 = 
    part2->getBody();

    std::string str_media_type2;
    std::string str_charset2;
    get_body_media_type( body2, str_media_type2, str_charset2 );

    std::string content2;
    get_body_content_utf8( body2, content2 );

    size_t 	count2 = body2->getPartCount();

    if (count2 == 0) {
        content = content2;
        return;
    }

 // multi-part
    vmime::shared_ptr<vmime::bodyPart> 	part3 =  body2->getPartAt(0);

    vmime::shared_ptr<vmime::body> body3 = part3->getBody();

    std::string content3 ;
    get_body_content_utf8( body3, content3 );

    content = content3;

    return;

}




/** 
 *    get_body_content_utf8
  */
void get_body_content_utf8( vmime::shared_ptr<vmime::body> body, std::string &content )
{

    std::string media_type;
    std::string charset ;
    get_body_media_type( body, media_type, charset );

    bool  is_iso2022jp = is_body_iso2022jp( media_type, charset );

    std::string str_body;
    extractBody(body, str_body );

    std::string plane_text;
    bool ret = getPlaneTextInBody(str_body,  plane_text );


    if(ret){
        content = plane_text;
    } else if(is_iso2022jp) {
        std::string utf8;
        iso2022jp_to_utf8(str_body, utf8);
        content = utf8;
    } else {
        content  = str_body;
    }

    return;
}



/** 
 *   get_body_media_type
  */
void get_body_media_type( vmime::shared_ptr<vmime::body> body, std::string &str_media_type, std::string &str_charset )
{
    const std::string MEDIA_TYPE_ISO2022JP = "text/iso-2022-jp";

    vmime::mediaType media_type = body->getContentType();

    str_media_type = media_type.generate();

    vmime::charset charset = body->getCharset();

    str_charset = charset.generate();

    return;
}


/** 
 *   is_body_iso2022jp
  */
bool is_body_iso2022jp( std::string media_type, std::string charset )
{
    const std::string MEDIA_TYPE_ISO2022JP = "text/iso-2022-jp";

// is_iso2022jp ?
    bool is_iso2022jp = false;
    if( isEqualNoCase( charset, CHARSET_ISO2022JP ) ) {
        is_iso2022jp = true;
    }

// python format
    if( isEqualNoCase(media_type, MEDIA_TYPE_ISO2022JP) ) {
        is_iso2022jp = true;
    }

    return is_iso2022jp;
}


/** 
 *   isEqualNoCase
  */
bool isEqualNoCase(const std::string s1, const std::string s2)
{
    return vmime::utility::stringUtils::isStringEqualNoCase( s1, s2 );
}

/** 
 *  getContentType
  */
void getContentType( vmime::shared_ptr <vmime::message> msg, std::string &type ) 
{

    type = msg->getHeader()->ContentType()->getValue()->generate();

}


/** 
 * getPlaneTextInBody
  */
bool getPlaneTextInBody(std::string src,  std::string &plane_text )
{

// take out the plane text  without headers,
// if body has headers,

// when parse body has no headers,
// ContentType is  "application/octet-stream"

    vmime::shared_ptr <vmime::message> msg = vmime::make_shared<vmime::message>();
    msg->parse( src );

    vmime::shared_ptr <vmime::body> body = msg->getBody();
    if(!body) {
        return false;
    }

    std::string type;
    getContentType( msg, type ) ;

    if ( type != "text/plain" ){
        return false;
    }

    std::string str_body;
    extractBody( body,  str_body );
    plane_text = str_body;

    return true;

}



/** 
 * extractBody
  */
void extractBody( vmime::shared_ptr<vmime::body> body,  
   std::string &str_body )
{

    vmime::string str_out;
	vmime::utility::outputStreamStringAdapter	out(str_out);

    vmime::string type
    =	body->getContentType().getType(); 

    vmime::shared_ptr<const vmime::contentHandler> cts  = body->getContents();

    if(type == "text") {
 	       cts->extract(out);
            str_body = str_out;
    }

    return;
}



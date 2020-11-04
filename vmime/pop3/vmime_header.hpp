#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for header

#include <string>
 #include "vmime/utility/stringUtils.hpp"
#include "vmime_charset.hpp"

// prototype
void getHeaders( vmime::shared_ptr <vmime::net::message> msg,  std::string &subject, std::string &from, std::string &date );
void decode_header( std::string raw, std::string &result);
void getFullHeaders(
vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg, std::string &headers);


/** 
 * getHeaders
  */
void getHeaders( vmime::shared_ptr <vmime::net::message> msg,  std::string &subject, std::string &from, std::string &date )
{

   vmime::shared_ptr< const vmime::header > header = msg->getHeader();

    auto header_subject = header->Subject();
	if(header_subject) {
            std::string subject_raw = header_subject->getValue()->generate();
            std::string result;
            decode_header( subject_raw, result );
            subject = result;
    } else {
            subject = "no subject";
    }


    auto header_from = header->From();
	if(header_from) {
	        std::string from_raw = header_from->getValue()->generate();
            std::string from_result;
            decode_header( from_raw, from_result );
            from = from_result;
    } else {
            from = "";
    }

    auto header_date = header->Date();
	if(header_date) {
	        date = header_date->getValue()->generate();
    } else {
            date = "";
    }

    return;
}


/**
 * decode_header
 */
void decode_header( std::string raw, std::string &result)
{

 std::string  charset_lower = vmime::utility::stringUtils::toLower(CHARSET_ISO2022JP);

// iso2022 ?
    bool is_iso2022 = false;
    int pos1 = raw.find( CHARSET_ISO2022JP );
    int pos2 = raw.find(  charset_lower );
    if(pos1 != std::string::npos){
            is_iso2022 = true;
    }
    if(pos2 != std::string::npos){
            is_iso2022 = true;
    }

    vmime::text text;
    vmime::text::decodeAndUnfold( raw, &text );
    vmime::string decoded = text.getWholeBuffer();


    if (is_iso2022 ) {
        vmime::string utf8;
        iso2022jp_to_utf8(decoded, utf8);
        result = utf8;
    } else {
        result = decoded ;
    }

}


/**
 *  getFullHeaders
  */
void getFullHeaders(
vmime::shared_ptr <vmime::net::folder> f,
vmime::shared_ptr <vmime::net::message> msg, std::string &headers)
{

        f->fetchMessage(msg, vmime::net::fetchAttributes::FULL_HEADER);

		headers = msg->getHeader()->generate();

}

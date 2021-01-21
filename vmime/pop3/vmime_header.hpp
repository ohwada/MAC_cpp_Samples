#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// function for header

#include <string>
#include "vmime/vmime.hpp"
#include "vmime/contentTypeField.hpp"


/** 
* struct HeaderInfo
  */
struct HeaderInfo
{
int msg_number;
std::string subject;
std::string from;
std::string to;
std::string date;
std::string message_id ;
std::string user_agent ;
std::string content_type;
std::string encoding;
std::string disposition;
std::string label;
};


// prototype
void getHeaderInfo( vmime::shared_ptr < vmime::header> hdr, struct HeaderInfo &info );
bool getSubject( vmime::shared_ptr < vmime::header> hdr, std::string &subject );
bool getFrom( vmime::shared_ptr < vmime::header> hdr, std::string &from );
bool getTo( vmime::shared_ptr < vmime::header> hdr, std::string &to );
bool getDate( vmime::shared_ptr < vmime::header> hdr, std::string &date );
bool getMessageId( vmime::shared_ptr < vmime::header> hdr, std::string &id );
bool  getContentType( vmime::shared_ptr < vmime::header> hdr, std::string &content_type );
bool  getContentTransferEncoding( vmime::shared_ptr < vmime::header> hdr, std::string &name );
bool getUserAgent( vmime::shared_ptr < vmime::header> hdr, std::string &ua );
bool  getContentDisposition( vmime::shared_ptr < vmime::header> hdr, std::string &name );
bool  getContentId( vmime::shared_ptr < vmime::header> hdr, std::string &id );
void printHeaderInfo( struct HeaderInfo info);


/**
 *  getHeaderInfo
 */
void getHeaderInfo( vmime::shared_ptr < vmime::header> hdr, struct HeaderInfo &info )
{

    const std::string COLON( " : "); 

    std::string subject;
    std::string from;
    std::string to;
    std::string date;
    std::string message_id ;
    std::string user_agent ;    
    std::string content_type;
    std::string encoding;
    std::string disposition;

    bool ret1 = getSubject( hdr, subject );
    if(ret1){
        info.subject = subject;
    }

    bool ret2 = getFrom( hdr, from );
    if(ret2){
        info.from = from;
    }

    bool ret3 = getTo( hdr, to );
    if(ret3){
        info.to = to;
    }

    bool ret4 = getDate( hdr, date );
    if(ret4){
        info.date = date;
    }

    bool ret5 = getMessageId( hdr, message_id );
    if(ret5){
        info.message_id = message_id;
    }

    bool ret6 = getUserAgent( hdr, user_agent );
    if(ret6){
        info.user_agent = user_agent;
    }

    bool  ret7 = getContentType(hdr, content_type );
    if(ret7){
        info.content_type = content_type;
    }

    bool  ret8 = getContentTransferEncoding( hdr, encoding );
    if(ret8){
        info.encoding = encoding;
    }

    bool  ret9 = getContentDisposition( hdr, disposition );
    if(ret9){
        info.disposition = disposition;
    }

    std::string label = subject + COLON + from;
    info.label = label;

}


/**
 *  getSubject
 */
bool getSubject( vmime::shared_ptr < vmime::header> hdr, std::string &subject )
{

    vmime::shared_ptr< const vmime::headerField > hdr_subject = hdr->Subject();

    if(!hdr_subject) {
        return false;
    }

    vmime::shared_ptr< const vmime::text > text_subject = hdr_subject->getValue<vmime::text>();

    if(!text_subject) {
        return false;
    }

    subject =  
    text_subject->getConvertedText(vmime::charsets::UTF_8);

    return true;
}


/**
 *   getFrom
 */
bool getFrom( vmime::shared_ptr < vmime::header> hdr, std::string &from )
{
    const std::string LEFT( " ( "); 
    const std::string RIGHT( " ) "); 

    vmime::shared_ptr< const vmime::headerField > hdr_from = hdr->From();

    if(!hdr_from) {
        return false;
    }

    vmime::shared_ptr< const vmime::mailbox > mailbox_from = hdr_from->getValue<vmime::mailbox>();

    if(!mailbox_from) {
        return false;
    }

    const vmime::text text_from_name = 
    mailbox_from->getName();

    const vmime::string str_from_name = 
    text_from_name.getConvertedText(vmime::charsets::UTF_8);

    vmime::emailAddress addr_from = mailbox_from->getEmail();
 
    if( addr_from.isEmpty() ) {
        return false;
    }

    vmime::string str_from_email = addr_from.toString(); 

    if( str_from_name.empty() ) {
        from = str_from_email;
    } else {
        from = str_from_name + LEFT + str_from_email + RIGHT ;
    }

    return true;
}


/**
 *   getTo
 */
bool getTo( vmime::shared_ptr < vmime::header> hdr, std::string &to )
{

    vmime::shared_ptr< const vmime::headerField > hdr_to = hdr->To();

    if(!hdr_to) {
        return false;
    }

    vmime::shared_ptr< const vmime::addressList > address_list = hdr_to->getValue<vmime::addressList>();

    if(!address_list) {
        return false;
    }

    if( address_list->isEmpty() ){
        return false;
    }

    vmime:: shared_ptr< const vmime::address > addr
    = address_list->getAddressAt(0);

    if( !addr ){
        return false;
    }

     to = addr->generate();

    return true;
}



/**
 *   getDate
 */
bool getDate( vmime::shared_ptr < vmime::header> hdr, std::string &date )
{
    vmime::shared_ptr< const vmime::headerField > hdr_date = hdr->Date();

	if(!hdr_date) {
        return false;
    }

    date = hdr_date->getValue()->generate();

    return true;

}


/**
 *   getMessageId 
 */
bool getMessageId ( vmime::shared_ptr < vmime::header> hdr, std::string &id )
{
    vmime::shared_ptr< const vmime::headerField > hdr_id = hdr->MessageId();

	if(!hdr_id) {
        return false;
    }

    vmime::shared_ptr< const vmime::messageId > messageid = hdr_id->getValue<vmime::messageId>();

    if(!messageid) {
        return false;
    }

    id = messageid->getId();

    return true;

}



/**
 *   getUserAgent
 */
bool getUserAgent( vmime::shared_ptr < vmime::header> hdr, std::string &ua )
{
    vmime::shared_ptr< const vmime::headerField > hdr_ua = hdr->UserAgent();

	if(!hdr_ua) {
        return false;
    }

    ua = hdr_ua->getValue()->generate();

    return true;

}


/**
 *    getContentType
 */
bool  getContentType( vmime::shared_ptr < vmime::header> hdr, std::string &content_type )
{

    const std::string SLASH( " / "); 
    const std::string COLON( " : "); 

    vmime::shared_ptr< const vmime::headerField > hdr_type = hdr->ContentType();

	if(!hdr_type) {
        return false;
    }

    vmime::shared_ptr< const vmime::mediaType > media_type = hdr_type->getValue<vmime::mediaType>();

	if(!media_type) {
        return false;
    }

    std::string type = media_type->getType();

    std::string subtype = media_type->getSubType();


    vmime::shared_ptr <vmime::contentTypeField> field =
    hdr->getField <vmime::contentTypeField>(vmime::fields::CONTENT_TYPE);

	if(!field) {
        return false;
    }

    std::string str_charset;

    if( field->hasCharset() ) {
        str_charset = field->getCharset().getName();
}

    content_type = type + SLASH + subtype;

    if( str_charset.size() > 0 ){
        content_type +=  COLON + str_charset;
    }

    return true;

}


/**
 *    getContentTransferEncoding
 */
bool  getContentTransferEncoding( vmime::shared_ptr < vmime::header> hdr, std::string &name )
{

    vmime::shared_ptr< const vmime::headerField > hdr_content_transfer = hdr->ContentTransferEncoding();

	if(!hdr_content_transfer) {
        return false;
    }

    vmime::shared_ptr< const vmime::encoding > encoding = hdr_content_transfer->getValue<vmime::encoding>();

    if(!encoding) {
        return false;
    }

    name = encoding->getName();

    return true;
}


/**
 *    getContentDisposition
 */
bool  getContentDisposition( vmime::shared_ptr < vmime::header> hdr, std::string &name )
{

    vmime::shared_ptr< const vmime::headerField > hdr_disposition = hdr->ContentDisposition();

	if(!hdr_disposition) {
        return false;
    }

    vmime::shared_ptr< const vmime::contentDisposition > disposition = hdr_disposition->getValue<vmime::contentDisposition>();

    if(!disposition) {
        return false;
    }

    name = disposition->getName();

    return true;
}



/**
 *    getContentId
 */
bool  getContentId( vmime::shared_ptr < vmime::header> hdr, std::string &id )
{

    vmime::shared_ptr< const vmime::headerField > hdr_id = hdr->ContentId();

	if(!hdr_id) {
        return false;
    }

    vmime::shared_ptr< const vmime::messageId > 	messageid = hdr_id->getValue<vmime::messageId>();

    if(!messageid ) {
        return false;
    }

    id = messageid->getId();

    return true;
}



/**
 *    printHeaderInfo
 */
void printHeaderInfo( struct HeaderInfo info)
{

    std::cout << "Subject: " << info.subject << std::endl;
    std::cout << "From: " << info.from << std::endl;
    std::cout << "To: " << info.to << std::endl;
    std::cout << "Date: " << info.date << std::endl;
    std::cout << " MessageId: " << info. message_id << std::endl;
    std::cout << " User Agent: " << info. user_agent << std::endl;
    std::cout << "ContentType: " << info.content_type << std::endl;
   std::cout << "ContentTransferEncoding: " << info.encoding << std::endl;
   std::cout << "ContentDisposition: " << info.disposition << std::endl;

};
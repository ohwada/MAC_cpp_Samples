/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "vmime/vmime.hpp"
#include "media_type.hpp"
#include "file_util.hpp"


// prototype
vmime::shared_ptr <vmime::message> 
buildMessageFile( std::string subject,  std::string body, std::string mail_from, std::string mail_to, std::string fullpath, std::string &error );
vmime::shared_ptr <vmime::message>
buildMessageCharset(std::string subject, std::string body, std::string mail_from, std::string mail_to, vmime::charset charset ) ;
vmime::shared_ptr <vmime::message> buildMessage( std::string subject, std::string body, std::string mail_from, std::string mail_to );
vmime::messageBuilder 
getMessageBuilder( std::string mail_from, std::string mail_to ) ;
std::string getDefaultBody(void );
vmime::shared_ptr <vmime::fileAttachment> createFileAttachment( std::string fullpath, std::string &error );
void getMediaTypeFromFullpath(std::string ext, vmime::mediaType &ret_type);
void getMediaTypeFromExt(std::string ext, vmime::mediaType &ret_type);
void getFileName(std::string fullpath, std::string &fname);
void getFileExt(std::string filename, std::string &ext);

// constant
const std::string CRLF = "\r\n";
 
const std::string MAILER  
	= std::string("VMime ") + std::string(VMIME_VERSION) ;


/**
 *  buildMessageFile
 */
vmime::shared_ptr <vmime::message> 
buildMessageFile( std::string subject,  std::string body, std::string mail_from, std::string mail_to, std::string fullpath, std::string &ret_error ) 
{

	// build message
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	// Adding an attachment
std::string error;
	vmime::shared_ptr <vmime::fileAttachment> att = createFileAttachment( fullpath, error );

    if(!att){
        ret_error = error;
        return vmime::null;
    }

	mb.attach(att);

	// construct
	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() ->UserAgent() -> setValue( MAILER );

    return msg;
}


/** 
 * buildMessageCharset
  */
vmime::shared_ptr <vmime::message> buildMessageCharset(std::string subject, std::string body, std::string mail_from, std::string mail_to, vmime::charset charset ) 
{

// build message 
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
    vmime::text text_subject( subject, charset );

	// mb.setSubject( vmime::text( subject, charset ) );
	mb.setSubject( text_subject );

// TextPart
    vmime::shared_ptr< vmime::textPart > part = 	mb.getTextPart();

   //  part->setCharset( vmime::charset( charset ) );
    part->setCharset( charset );

    part->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	// construct
    vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}


/** 
 * buildMessage
  */
vmime::shared_ptr <vmime::message> buildMessage( std::string subject, std::string body, std::string mail_from, std::string mail_to ) 
{

	vmime::messageBuilder mb = getMessageBuilder( mail_from, mail_to );

// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}


/** 
 * getMessageBuilder
  */
vmime::messageBuilder 
getMessageBuilder( std::string mail_from, std::string mail_to ) 
{

// build message 
	vmime::messageBuilder mb;

// standard  header
	mb.setExpeditor(vmime::mailbox(mail_from));

	vmime::addressList to;
	to.appendAddress(vmime::make_shared <vmime::mailbox>(mail_to));
	mb.setRecipients(to);

    return mb;
}


/** 
 * getDefaultBody
  */
std::string getDefaultBody(void )
{
// build body 
	const std::string body = 
	std::string( "This is is a test e-mail." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;

	return body;
}


/**
 *  createFileAttachment
 */
	vmime::shared_ptr <vmime::fileAttachment> createFileAttachment( std::string fullpath, std::string &error )
{

    if( !existsFile(fullpath) ){
        error = "not found: " + fullpath;
        return vmime::null;
    }

    std::string fname;
    getFileName(fullpath, fname);

	vmime::mediaType media_type;
    getMediaTypeFromFullpath(fullpath,  media_type);

	vmime::shared_ptr <vmime::fileAttachment> att =
	vmime::make_shared <vmime::fileAttachment>(
		fullpath, 
		media_type );

	att->getFileInfo().setFilename( fname);

	vmime::datetime now = vmime::datetime::now();

	att->getFileInfo().setCreationDate(now);

	return att;
}


/**
 *  getMediaTypeFromFullpath
 */
void getMediaTypeFromFullpath(std::string fullpath, vmime::mediaType &type)
{
    std::string ext;
    getFileExt(fullpath, ext);

    getMediaTypeFromExt( ext, type);
}


/**
 *  getMediaTypeFromExt
 */
void getMediaTypeFromExt(std::string ext, vmime::mediaType &ret_type)
{

    std::string str_type;
	getMediaType(ext, str_type);

	vmime::mediaType media_type( str_type );
    ret_type = media_type;
}


/**
 *  getFileName
 */
void getFileName(std::string fullpath, std::string &fname)
{

    const char SLASH = '/';

	std::string fn(fullpath);
	std::string::size_type p = fn.find_last_of(SLASH);

	if (p != std::string::npos){
		p += 1; // get past folder delimeter
		fname = fn.substr(p, fn.length() - p);
	}

}


/**
 *  getFileEXt
 */
void getFileExt(std::string filename, std::string &ext)
{

    const char DOT = '.';

	std::string fn(filename);
	std::string::size_type p = fn.find_last_of(DOT);

	if (p != std::string::npos){
		p += 1; // get past folder delimeter
		ext = fn.substr(p, fn.length() - p);
	}

}
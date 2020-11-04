/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

#include "vmime/vmime.hpp"
#include "media_type.hpp"
#include "parse_filename.hpp"


// prototype
vmime::shared_ptr <vmime::message> 
buildMessageFile( std::string subject,  std::string body, std::string mail_from, std::string mail_to, std::string fullpath );
vmime::shared_ptr <vmime::message>
buildMessageCharset(std::string subject, std::string body, std::string mail_from, std::string mail_to, std::string charset ) ;
vmime::shared_ptr <vmime::message> buildMessage( std::string subject, std::string body, std::string mail_from, std::string mail_to );
vmime::messageBuilder 
getMessageBuilder( std::string mail_from, std::string mail_to ) ;
std::string getDefaultBody(void );


// constant
const std::string CRLF = "\r\n";
 
const std::string MAILER  
	= std::string("VMime ") + std::string(VMIME_VERSION) ;


/**
 *  buildMessageFile
 */
vmime::shared_ptr <vmime::message> 
buildMessageFile( std::string subject,  std::string body, std::string mail_from, std::string mail_to, std::string fullpath ) 
{


	std::string filename = getFileNameWithExt( fullpath );
 	std::string ext = getFileNameExt(fullpath);

	std::string media_type;
	getMediaType(ext, media_type);

	// build message
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	// Adding an attachment
	vmime::datetime now = vmime::datetime::now();

	vmime::shared_ptr <vmime::fileAttachment> att =
	vmime::make_shared <vmime::fileAttachment>(
		fullpath,  // full path to file
		vmime::mediaType( media_type ) 
		);

	
	att->getFileInfo().setFilename( filename);

	att->getFileInfo().setCreationDate(now);

	mb.attach(att);


	// construct
	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}


/** 
 * buildMessageCharset
  */
vmime::shared_ptr <vmime::message> buildMessageCharset(std::string subject, std::string body, std::string mail_from, std::string mail_to, std::string charset ) 
{

// build message 
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
	mb.setSubject( vmime::text( subject, charset ) );


// TextPart
    vmime::shared_ptr< vmime::textPart > part = 	mb.getTextPart();
    part->setCharset( vmime::charset( charset ) );

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



/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with HTML and embedded image to SMTP server 

// This sample program demonstrate the use of the messageBuilder component
// to build a complex message (HTML content, plain text and embedded image)
// reference : https://github.com/kisli/vmime/blob/master/examples/example3.cpp


#include <iostream>
#include "smtp.hpp"
#include "executable_path.hpp"
#include "certificateVerifier_nubntu.hpp"

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, string exe_path )
{

const string IMAGE_PNG = "png";

// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has TML and embedded image." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;

	cout << body << endl;


	// build message
	vmime::messageBuilder mb = 
	getMessageBuilder( mail_from, mail_to );

// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

// Set the content-type to "text/html"
		mb.constructTextPart(
			vmime::mediaType(
				vmime::mediaTypes::TEXT,
				vmime::mediaTypes::TEXT_HTML
			)
		);

		// Fill in the text part: the message is available in two formats: HTML and plain text.
		// HTML text part also includes an inline image (embedded into the message).
		vmime::htmlTextPart& textPart =
			*vmime::dynamicCast <vmime::htmlTextPart>(mb.getTextPart());

		// -- embed an image (the returned "CID" (content identifier) is used to reference
		// -- the image into HTML content).
		vmime::shared_ptr <vmime::utility::fileSystemFactory> fs = 
			vmime::platform::getHandler()->getFileSystemFactory();

	string dir = exe_path + string("data/") ;
	string fname( "baboon.png" );

	string fullpath = dir + fname; 
	cout << "fullpath: " << fullpath << endl;

	vmime::shared_ptr <vmime::utility::file> imageFile =
			fs->create(fs->stringToPath(fullpath));

		vmime::shared_ptr <vmime::utility::fileReader> fileReader =
			imageFile->getFileReader();

		vmime::shared_ptr <vmime::contentHandler> imageCts =
			vmime::make_shared <vmime::streamContentHandler>(
				fileReader->getInputStream(),
				imageFile->getLength()
			);

		vmime::shared_ptr <const vmime::htmlTextPart::embeddedObject> obj =
			textPart.addObject(
				imageCts,
				vmime::mediaType(
					vmime::mediaTypes::IMAGE,
					IMAGE_PNG
				)
			);

// html message
	string html = string( "This is the <b>HTML</b> text. <br/><br/>" )
	+ string( "this mail has <b>embed image</b>. <br/><br/>" )
	+ string("<img src=\"" ) 
	+ obj->getReferenceId() 
	+ string( "\"/>" );

	cout << html << endl;

		// text message
		textPart.setText( 
			vmime::make_shared <vmime::stringContentHandler>(
			html )
		);

		textPart.setPlainText(
			vmime::make_shared <vmime::stringContentHandler>(
				body )
		);

	// construct
	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}



/**
 *  main
 */
int main(int argc, char **argv)
{
 const	std::string  SUBJECT = "vmime embed";

	string path = getExecutablePathDir(argv[0] );
	cout << "ExecutablePathDir: " << path << endl;

	bool is_save = true;

   bool verbose = true;

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

    vmime::shared_ptr <vmime::message> msg = 
buildCustomMessage(  SUBJECT, FROM, TO, path);

    if(is_save){
        saveMessage( msg ) ;
    }


	vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();
    bool ret = sendMessage( g_session, URL,  USER,  PASSWD,  
    msg, cv, verbose ) ;

    if(!ret){
        cout << "send mail failed" << endl;
        return 1;
    }

    cout << "send mail successful" << endl;
	return 0;
}
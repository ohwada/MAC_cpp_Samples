/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with HTML to SMTP server 


// reference : https://github.com/kisli/vmime/blob/master/examples/example3.cpp


#include <iostream>
#include "smtp_ubuntu.hpp"
#include "executable_path.hpp"


using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to )
{

	std::string body = "";

// plain message
	std::string plain = std::string("this is a test mail ")
	+ CRLF
	+ std::string( "this mail has html" )
	+ CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  
	+ CRLF;

	std::cout << plain << std::endl;

// html message
	std::string html = std::string( "This is a test mail.<br/>" )
  	+ CRLF
	+ std::string( "This mail has <b>HTML</b> <br/>" )
  	+ CRLF
	+ std::string( "This mail was sent using <b> ")
    + MAILER  
	+ std::string( " </b> <br/>")
	+ CRLF;
	
	cout << html << endl;

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

		// text message
		textPart.setText( 
			vmime::make_shared <vmime::stringContentHandler>(
			html )
		);

		textPart.setPlainText(
			vmime::make_shared <vmime::stringContentHandler>(
				plain )
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

	const	std::string  SUBJECT = "vmime html";

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
buildCustomMessage(  SUBJECT, FROM, TO );

    if(is_save){
        saveMessage( msg ) ;
    }

	vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();

    bool ret = sendMessage( g_session, URL,  USER,  PASSWD,  
    msg, cv, verbose ) ;

 if(ret){
    cout << "send mail successful" << endl;
	} else {
        cerr << "send mail failed" << endl;
         return EXIT_FAILURE;
    }

	    return EXIT_SUCCESS;
}

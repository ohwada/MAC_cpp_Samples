/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with Two attaced files to Ubuntu SMTP server

//  g++ smtp/smtp_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include "smtp_ubuntu.hpp"
#include "executable_path.hpp"


// prototype
	vmime::shared_ptr <vmime::fileAttachment> createFileAttachment( std::string fullpath );

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, string fullpath1, string fullpath2, std::string error ) 
{

// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has two attachments." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;


	// build message
std::string error1;
vmime::shared_ptr <vmime::fileAttachment>  att1 = createFileAttachment( fullpath1, error1 );

if(!att1){
    error = error1;
    return vmime::null;
}

std::string error2;
vmime::shared_ptr <vmime::fileAttachment>  att2 = createFileAttachment( fullpath2, error2 );

if(!att2){
    error = error2;
    return vmime::null;
}

	// build message
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	// Adding an attachment
	mb.attach(att1);
	mb.attach(att2);


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
	 const	string  SUBJECT = "vmime attach 2";

    bool verbose = true;

	string exe_path = getExecutablePathDir(argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath1 = "data/baboon.png";
	string filepath2 = "data/sample_ascii.txt";

	bool is_save = true;

    if(argc == 3) {
      	filepath1 = argv[1];
      	filepath2 = argv[2];
    } else {
        cout << "Usage: " << argv[0] << " [file1] [file2] "  << endl;
    }

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

	string fullpath1 = exe_path + filepath1;
	string fullpath2 = exe_path + filepath2;

    std::string error;
    vmime::shared_ptr <vmime::message> msg = buildCustomMessage(  SUBJECT, FROM, TO, fullpath1,  fullpath2, error );

    if(!msg){
        cerr << error << endl;
         return EXIT_FAILURE;
    }

    if(is_save){
        saveMessage( msg ) ;
    }

	vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();
    bool ret = sendMessage( g_session, URL,  USER,  PASSWD,  
    msg, cv, verbose );

    if(ret){
    cout << "send mail successful" << endl;
	} else {
        cout << "send mail failed" << endl;
         return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with attaced files to SMTP server

//  g++ smtp/smtp_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include "smtp.hpp"
#include "executable_path.hpp"
#include "certificateVerifier_nubntu.hpp"
#include "parse_filename.hpp"

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, string fullpath ) 
{

// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has one attachments." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;


	// build message
	return buildMessageFile( subject,  body, mail_from, mail_to, fullpath ); 
}



/**
 *  main
 */
int main(int argc, char **argv)
{
	 const	string  SUBJECT = "vmime attach";

    bool verbose = true;

	string exe_path = getExecutablePathDir(argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath = "data/baboon.png";
	bool is_save = true;

    if(argc == 3) {
      	filepath = argv[1];
        is_save = (bool)atoi(argv[2] );
    } else if (argc == 2) {
      	filepath = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file ] [save] "  << endl;
    }

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

	string fullpath = exe_path + string("/") + filepath;
    vmime::shared_ptr <vmime::message> msg = buildCustomMessage(  SUBJECT, FROM, TO, fullpath );

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
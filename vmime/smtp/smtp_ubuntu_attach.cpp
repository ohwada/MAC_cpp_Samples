/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with attaced files to Ubuntu SMTP server

//  g++ smtp/smtp_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include "smtp_ubuntu.hpp"
#include "executable_path.hpp"


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, std::string fullpath, std::string &ret_error ) 
{

    if( !existsFile(fullpath) ){
        ret_error = "not found: " + fullpath;
        return vmime::null;
    }

// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has one attachments." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;


	// build message
    std::string error;
	auto ret = buildMessageFile( subject,  body, mail_from, mail_to, fullpath, error ); 

    if(!ret){
        ret_error = error;
        return vmime::null;
    }

    return ret;
}


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{
	 const	string  SUBJECT = "vmime attach";

    bool verbose = true;

	string exe_path = getExecutablePathDir( argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath( "data/baboon.jpg" );

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

	string fullpath = exe_path + filepath;

    cout << " fullpath: " <<  fullpath << endl;

    std::string error;
    vmime::shared_ptr <vmime::message> msg = buildCustomMessage(  SUBJECT, FROM, TO, fullpath, error );

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
        cerr << "send mail failed" << endl;
         return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

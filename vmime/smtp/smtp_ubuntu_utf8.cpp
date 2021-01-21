/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with UTF8 to Ubuntu SMTP server
 
#include <iostream>
#include "smtp_ubuntu.hpp"


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();



/** 
 * buildCustomMessage
  */
vmime::shared_ptr <vmime::message> buildCustomMessage(std::string mail_from, std::string mail_to ) 
{

    const vmime::charset CHARSET( vmime::charsets::UTF_8 );

    const std::string  SUBJECT = u8"vmime utf8 テスト";


// build body 
	const std::string body = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは UTF-8 です。" )
     + CRLF
	 + std::string( u8"このメールは下記の Mailer を使って送信されました。" )
     + CRLF
	 + std::string( "Mailer: " )
    +  MAILER  + CRLF;

    std::cout << body << std::endl;


// build message 
    return buildMessageCharset( SUBJECT, body,  mail_from, mail_to, CHARSET ) ;

}


using namespace std;


/**
 *  main
 */
int main(void)
{

    bool verbose = true;

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );
    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

    vmime::shared_ptr <vmime::message> msg = buildCustomMessage( FROM, TO ) ;

 
    saveMessage( msg ) ;

	shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();
    bool ret = sendMessage( g_session, URL,  USER,  PASSWD,  
        msg, cv, verbose ) ;

    if(ret){
    cout << "send mail successful" << endl;
	} else {
        cout << "send mail failed" << endl;
         return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

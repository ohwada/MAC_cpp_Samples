/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with ISO2022JP to Ubuntu SMTP server
 
#include <iostream>
#include "smtp_ubuntu.hpp"
#include "vmime_charset.hpp"

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/** 
 * buildCustomMessage
  */
vmime::shared_ptr <vmime::message> buildCustomMessage(std::string mail_from, std::string mail_to ) 
{

    const string  SUBJECT = u8"vmime iso2022jp テスト";



// build body 
	const std::string body_utf8 = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは ISO-2022-JP です。" )
     + CRLF
	 + std::string( u8"このメールは下記の Mailer を使って送信されました。" )
     + CRLF
	 + std::string( "Mailer: " )
    +  MAILER  + CRLF;


// iso2022jp
    string subject_iso2022;
    from_utf8(SUBJECT, subject_iso2022, CHARSET_ISO2022JP );

    string body_iso2022;
    from_utf8(body_utf8, body_iso2022,  CHARSET_ISO2022JP );


// build message 
    return buildMessageCharset( subject_iso2022, body_iso2022,  mail_from, mail_to,  CHARSET_ISO2022JP ) ;

}


/**
 *  main
 */
int main(int argc, char **argv)
{

    bool verbose = true;

	bool is_save = true;

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );
    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


    vmime::shared_ptr <vmime::message> msg = buildCustomMessage( FROM, TO ) ;

    // printMessage( msg ) ;

    if(is_save){
        saveMessage( msg ) ;
    }

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

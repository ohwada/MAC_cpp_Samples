/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail with ISO2022JP to SMTP server
 
#include <iostream>
#include "smtp.hpp"
#include "certificateVerifier_nubntu.hpp"
#include "vmime_charset.hpp"

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();



/** 
 * buildCustomMessage
  */
vmime::shared_ptr <vmime::message> buildCustomMessage(std::string mail_from, std::string mail_to ) 
{

    const string CHARSET = CHARSET_ISO2022JP;

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
    utf8_to_iso2022jp(SUBJECT, subject_iso2022);

    string body_iso2022;
    utf8_to_iso2022jp(body_utf8, body_iso2022);


// build message 
    return buildMessageCharset( subject_iso2022, body_iso2022,  mail_from, mail_to, CHARSET ) ;

}


/**
 *  main
 */
int main(int argc, char **argv)
{

    bool verbose = true;

	int save = 0;
    if(argc == 2) {
        save = atoi(argv[1] );
    } else {
        cout << "Usage: " << argv[0] << " [save] "  << endl;
    }

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

    if(save){
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

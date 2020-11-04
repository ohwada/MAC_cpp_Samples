/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail to OCN SMTP server


#include <iostream>
#include "smtp.hpp"
#include "certificateVerifier.hpp"

using namespace std;

// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();

/**
 *  main
 */
int main(void) 
{
    const std::string  SUBJECT = "vmime test";

    bool verbose = true;

    setLocale("");

    MailParam  p = getOcnMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


    std::string body = getDefaultBody();
    vmime::shared_ptr <vmime::message> msg = buildMessage( SUBJECT, body, FROM, TO) ;


    printMessage( msg ) ;

	vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();
	
    bool ret = sendMessage(  g_session, URL, USER, PASSWD, msg, cv, verbose ) ;

    if(ret){
    cout << "send mail successful" << endl;
	} else {
        cout << "send mail failed" << endl;
         return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

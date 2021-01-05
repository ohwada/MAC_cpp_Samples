/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

//  send mail to Gmail SMTP server with xoauth2


// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/05/093009


// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. login Gmail server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include <string>
#include "vmime/security/sasl/XOAuth2SASLMechanism.hpp"
#include "vmime/security/sasl/XOAuth2SASLAuthenticator.hpp"
#include "certificateVerifier_gmail.hpp"
#include "access_token.hpp"
#include "smtp.hpp"

using namespace std;

// prototype
vmime::shared_ptr <vmime::net::transport>
getTransportXoauth(vmime::shared_ptr <vmime::net::session> session, string smtp_url);


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  getTransport
 */
vmime::shared_ptr <vmime::net::transport>
getTransportXoauth(vmime::shared_ptr <vmime::net::session> session, string smtp_url)
{

// Indicate that we want to use XOAUTH2 SASL mechanism
vmime::security::sasl::SASLMechanismFactory::getInstance()->
    registerMechanism <vmime::security::sasl::XOAuth2SASLMechanism>("XOAUTH2");

// Use a custom authenticator to force using XOAUTH2 mechanism
    vmime::shared_ptr <vmime::security::authenticator> xoauth2Auth =
    vmime::make_shared <vmime::security::sasl::XOAuth2SASLAuthenticator>
       (vmime::security::sasl::XOAuth2SASLAuthenticator::MODE_EXCLUSIVE);

    // Create a new SMTPS service to GMail
    vmime::shared_ptr <vmime::net::transport> tr = session->getTransport(
    vmime::utility::url(smtp_url), xoauth2Auth
);

	return tr;
}


/**
 *  main
 */
int main(void)
{

    const string  SUBJECT = "vmime xoauth";

    const string REFRESH_FILE( "refresh_token_mail.json");
 
     setLocale("");

    MailParam  p = getGmailParam();
    printMailParam( p );
    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

    string access_token;
    bool is_access_save = true;
    bool verbose1 = false;

    bool ret1 = getNewAccessToken( SCOPE_MAIL, 
    REFRESH_FILE,
    access_token, 
    is_access_save, verbose1);

    if(!ret1){
        cout << "getNewAccessToken failed" << endl;
        return 1;
    }

    cout << "access_token: " << access_token << endl;


    std::string body = getDefaultBody();
    vmime::shared_ptr <vmime::message> msg = buildMessage( SUBJECT, body, FROM, TO) ;

    printMessage( msg ) ;

	vmime::shared_ptr <vmime::net::transport> tr =
		getTransportXoauth( g_session, URL );


	tr->setProperty("options.need-authentication", true);
	tr->setProperty("auth.username",  USER);
	tr->setProperty("auth.accesstoken",  access_token);

    vmime::shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();

    bool verbose2 = true;
	bool ret9 = sendMsgSecure( tr,  msg, cv, verbose2 ) ;
    if(!ret9){
        cout << "send mail failed" << endl;
        return 1;
    }

    cout << "send mail successful" << endl;

	return 0;
}


// C: Connecting to smtp.gmail.com, port 587
// S: 220 smtp.gmail.com ESMTP 
// C: AUTH XOAUTH2 dXNlcj4BAQ==
// S: 235 2.7.0 Accepted


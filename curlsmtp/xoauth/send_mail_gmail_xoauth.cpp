/**
 * curlsmtp sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server with xoauth

// g++ curlsmtp/send_mail_gmail_xoauth.cpp curlsmtp/curlsmtp.cpp  -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` 

// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. login Gmail server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include <string>
#include <vector>
#include "../src/curlsmtp_util.hpp"
#include "access_token.hpp"


using namespace std;

/**
 * main
 */
int main(void)
{

	const std::string SUBJECT( "curlsmtp xoauth" );

    const string REFRESH_FILE("refresh_token_mail.json");

    const string MAIL_DIR( getMailDir() );

    struct MailParam p = getGmailParam();
    printMailParam( p );

    string SMTP_URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


    string access_token;
   string error;
    bool verbose_access = false;
    bool is_access_save = true;

    bool ret1 = getNewAccessToken( SCOPE_MAIL, 
    MAIL_DIR,
    REFRESH_FILE,
    access_token,  
    error,
    is_access_save, verbose_access);

    if(!ret1){
        return EXIT_FAILURE;
    }

    cout << "access_token: " << access_token << endl;

	bool is_verbose = true;
    bool is_save = true;
    bool is_verify = true;

	string msg = getDefaultMessage();

	CurlSmtp* mail = new CurlSmtp(SMTP_URL);

	 mail->set_user( USER );

	 // mail->set_password( PASSWD );
 	mail->set_token( access_token );

	 mail->set_from( FROM );
	 mail->set_to( TO );
	 mail->set_subject( SUBJECT );
 	mail->set_message( msg );
	mail->set_ssl_verify( is_verify );
	mail->set_verbose( is_verbose );

    if (is_save){
	   	    string msg = mail->get_send_buffer();
	          saveMail(msg);
    }

	bool ret2 = mail->send_mail();

    int exit;
    if(ret2){
        cout << "send mail successful" << endl;
        exit =  EXIT_SUCCESS;
    } else {
        string err = mail->get_error();
        cout << err << endl;
        exit =  EXIT_FAILURE;
    }

	sleep(5);
	delete mail;

    return exit;
}


// Connected to smtp.gmail.com



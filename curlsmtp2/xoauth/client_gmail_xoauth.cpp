/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server with xoauth

// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. login Gmail server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include <string>
#include <vector>
#include "../src/curlsmtp2_util.hpp"
#include "access_token.hpp"


using namespace std;

/**
 * main
 */
int main(void)
{

	const std::string SUBJECT( "curlsmtp2 xoauth" );

    const string REFRESH_FILE("refresh_token_mail.json");

    const string MAIL_DIR( getMailDir() );

    struct MailParam p = getGmailParam();
    printMailParam( p );

    string URL = p.smtp_url;
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
    cout << endl;

	bool is_verbose = true;
    bool is_save = true;
    bool is_verify = true;

	string msg = getDefaultMessage();

	CurlSmtp2* mail = new CurlSmtp2();

	 mail->set_url( URL );
	 mail->set_user( USER );
 	mail->set_token( access_token );
	 mail->set_from( FROM );
	 mail->set_str_to( TO );
	 mail->set_subject( SUBJECT );
 	mail->set_message( msg );
	mail->set_ssl_verify( is_verify );
	mail->set_verbose( is_verbose );

	bool ret2 = mail->send_mail2(error);

	sleep(5);
	delete mail;

    if(!ret2){
        cerr << "failed: " << error << endl;
        return EXIT_FAILURE;
    }

    cout << "sucessful" << endl;

    return EXIT_SUCCESS;
}


/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail with UTF-8 encoding to SMTP server 

#include <iostream>
#include <string>
#include <vector>
#include "curlsmtp_util.hpp"


using namespace std;


/**
 * main
 */
int main(void)
{

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    string SMTP_URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

    const string CHARSET = "UTF-8";

    const string  SUBJECT = u8"curlsmtp utf8 テスト";


// build message
	const std::string msg = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは UTF-8 です。" )
     + CRLF
	 + std::string( u8"このメールは CurlSmtp を使って送信されました。" )
     + CRLF;

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;

	CurlSmtp* mail = new CurlSmtp(SMTP_URL);

	 mail->set_user( USER );
	 mail->set_password( PASSWD );
	 mail->set_from( FROM );
	 mail->set_to( TO );
	 mail->set_subject_charset( SUBJECT, CHARSET );
 	mail->set_message_charset( msg, CHARSET );
	mail->set_ssl_verify(verify);
	mail->set_verbose(verbose);

    if (is_save){
	    string msg = mail->get_send_buffer();
	    saveMail(msg);
    }

	bool ret = mail->send_mail();

    int exit;
    if(ret){
        cout << "send mail successful" << endl;
        exit =  EXIT_SUCCESS;
    } else {
        string error = mail->get_error();
        cout << error << endl;
        exit =  EXIT_FAILURE;
    }

	sleep(5);
	delete mail;

	return exit;
}
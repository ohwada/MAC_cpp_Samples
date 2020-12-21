/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// send mail with UTF-8 encoding to SMTP server 


#include <iostream>
#include "curlsmtp2_util.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    //string SERVER = p.smtp_server;
    //int PORT = p.smtp_port;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


// subject
    const string  SUBJECT = u8"curlsmtp utf8 テスト";
    const string CHARSET = "UTF-8";


// build message
	const std::string msg = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは UTF-8 です。" )
     + CRLF
	 + std::string( u8"このメールは CurlSmtp2 を使って送信されました。" )
     + CRLF;

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;

	CurlSmtp2* mail = new CurlSmtp2();

	 mail->set_url( URL );
	 mail->set_user( USER );
	 mail->set_password( PASSWD );
	 mail->set_from( FROM );
	 mail->set_str_to( TO );
	 mail->set_subject_charset( SUBJECT, CHARSET );
 	mail->set_message_charset( msg, CHARSET );
	mail->set_ssl_verify(verify);
	mail->set_verbose(verbose);

    if (is_save){
	    string msg = mail->get_send_buffer();
	    saveMail(msg);
    }

	mail->send_mail();

	sleep(5);
	delete mail;

	return  EXIT_SUCCESS;;
}
/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// send mail with UTF-8 encoding and attached file to SMTP server 


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
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


// subject
    const string  SUBJECT = u8"curlsmtp2 添付あり";
    const string CHARSET = "UTF-8";


// build message
	const std::string msg = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは UTF-8 です。" )
     + CRLF
	+ std::string( u8"１つの添付ファイルが同封されています。" )
     + CRLF
	 + std::string( u8"このメールは CurlSmtp2 を使って送信されました。" )
     + CRLF;

	string file( "data/baboon.png" );

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;

    string buffer;
    string error;

	CurlSmtp2* mail = new CurlSmtp2();

	 mail->set_url( URL );
	 mail->set_user( USER );
	 mail->set_password( PASSWD );
	 mail->set_from( FROM );
	 mail->set_str_to( TO );
	 mail->set_subject_charset( SUBJECT, CHARSET );
 	mail->set_message_charset( msg, CHARSET );
	 mail->set_str_attach( file );
	mail->set_ssl_verify(verify);
	mail->set_verbose(verbose);

    if (is_save){
	    bool ret1 = mail->get_send_buffer(buffer, error);
        if(ret1){
	        saveMail(buffer);
            cout << endl;
        } else {
            cerr << "get_send_buffer: " << error << endl;
            return EXIT_FAILURE;
        }
    }

	bool ret2 = mail->send_mail2(error);

	sleep(5);
	delete mail;

if(!ret2){
    cerr << "failed: " << error << endl;
    return EXIT_FAILURE;
}

    cout << "sucessful" << endl;

	return  EXIT_SUCCESS;;
}
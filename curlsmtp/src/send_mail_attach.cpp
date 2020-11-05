/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail with attached file to SMTP server 


#include <iostream>
#include "curlsmtp_util.hpp"




/**
 * getMessage
 */
std::string getMessage(void)
{
   size_t BUFSIZE = 100;
    char buf[BUFSIZE];

	const std::string MSG1("This is a test e-mail.");
 	const std::string MSG2( "This mail has one attached file");
 	const std::string MSG3( "This mail was sent using CurlSmtp");

    snprintf(buf, BUFSIZE, "and %s \r\n", getCurlVersion() );
	const std::string MSG4( buf );

	std::string msg =
	MSG1 +CRLF
	+ MSG2 +CRLF
	+ MSG3 + CRLF
	+ MSG4 +CRLF;

	return msg;
}


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


	const std::string SUBJECT( "curlsmtp attach" );

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;


	string msg = getMessage();

	string attach( "data/baboon.png" );

	CurlSmtp* mail = new CurlSmtp(SMTP_URL);

	 mail->set_user( USER );
	 mail->set_password( PASSWD );
	 mail->set_from( FROM );
	 mail->set_to( TO );
	 mail->set_subject( SUBJECT );
 	mail->set_message( msg );
	mail->set_attach(attach);
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
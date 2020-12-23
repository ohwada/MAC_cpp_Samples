/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// send mail with attached file to SMTP server



#include <iostream>
#include "curlsmtp2_util.hpp"



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

    snprintf(buf, BUFSIZE, "and %s \r\n", getLibcurlVersion() );
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
int main(void )
{

   struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


	string subject = "curlsmtp2 attach";

	string message = getMessage();

	cout << message << endl;
	cout << endl;

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
	mail->set_subject(subject);
	mail->set_message(message);
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

	return EXIT_SUCCESS;;
}


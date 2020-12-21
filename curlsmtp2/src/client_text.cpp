/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// send mail with plain text to SMTP server


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
    string MAIL_FROM = p.from;
    string MAIL_TO =  p.to;


	string subject = "curlsmtp2 test";

	string message = getDefaultMessage();

	cout << message << endl;
	cout << endl;

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;

	CurlSmtp2* mail = new CurlSmtp2();

	 mail->set_url( URL );
	mail->set_user(USER);
	mail->set_password(PASSWD);
	mail->set_str_to(MAIL_TO);
	mail->set_from(MAIL_FROM);
	mail->set_subject(subject);
	mail->set_message(message);
	mail->set_ssl_verify(verify);
	mail->set_verbose(verbose);

    string msg = mail->get_send_buffer();
    cout << msg << endl;
	cout << endl;

	mail->send_mail();

	sleep(5);
	delete mail;

	return EXIT_SUCCESS;;
}


/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client 
// send mail to Gmail SMTP server


#include <iostream>
#include "curlsmtp2_util.hpp"


using namespace std;


/**
 * main
 */
int main(void )
{

   struct MailParam p = getGmailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


	string subject = "curlsmtp2 test";

	string message = getDefaultMessage();

	cout << message << endl;
	cout << endl;

    bool verify = true;

	bool verbose = true;

	CurlSmtp2* mail = new CurlSmtp2();

	 mail->set_url( URL );
	mail->set_user(USER);
	mail->set_password(PASSWD);
	mail->set_str_to(TO);
	mail->set_from(FROM);
	mail->set_subject(subject);
	mail->set_message(message);
    mail->set_ssl_verify(verify);
	mail->set_verbose(verbose);

	mail->send_mail();

	sleep(5);
	delete mail;

	return EXIT_SUCCESS;;
}


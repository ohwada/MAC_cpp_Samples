/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// send mail to Gmail SMTP server 


#include <iostream>
#include "curlsmtp_util.hpp"



using namespace std;


/**
 * main
 */
int main(void)
{

    struct MailParam p = getGmailParam();
    printMailParam( p );

    string SMTP_URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


	const std::string SUBJECT( "curlsmtp test" );

	bool verbose = true;

    bool is_save = true;

    bool verify = true;

	string msg = getDefaultMessage();

	CurlSmtp* mail = new CurlSmtp(SMTP_URL);

	 mail->set_user( USER );
	 mail->set_password( PASSWD );
	 mail->set_from( FROM );
	 mail->set_to( TO );
	 mail->set_subject( SUBJECT );
 	mail->set_message( msg );
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


// Connected to smtp.gmail.com




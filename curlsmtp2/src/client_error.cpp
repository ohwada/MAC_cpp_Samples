/**
 * curlsmtp2 sample
 * 2020-07-01 K.OHWADA
 */

// SMTP Client
// send mail with plain text to SMTP server

// cd /Users/ohwada/github/MAC_cpp_Samples/curlsmtp2
// bash src/build_client_error.sh


#include <iostream>
#include <glog/logging.h>
#include "curlsmtp2_util.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    google::InitGoogleLogging(argv[0]);

// set a signal handler that emits a stack trace on CRASH
     google::InstallFailureSignalHandler();


   struct MailParam p = getUbuntuMailParam();
    printMailParam( p );

    string URL = p.smtp_url;
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;

    TO = "jiro";
// <jiro>: Recipient address rejected: User unknown in local recipient table
// curl_easy_perform() failed: Failed sending data to the peer 

	string subject = "curlsmtp2 test";

	string message = getDefaultMessage();

	cout << message << endl;
	cout << endl;

	bool verbose = true;

    bool is_save = true;

// skip SSL verification 
// because ubuntu server is self-certified
    const bool verify = false;

    string error;

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

	bool ret = mail->send_mail2(error);

	sleep(5);
	delete mail;

if(!ret){
    cerr << "failed: " << error << endl;
    return EXIT_FAILURE;
}

    cout << "sucessful" << endl;

	return EXIT_SUCCESS;
}


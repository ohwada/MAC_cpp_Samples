// https://github.com/honeyligo/curlsmtp/blob/master/main.cpp

// g++ client_gmail.cpp curlsmtp.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp`


#include <iostream>
#include <string>
#include <unistd.h>
#include "curlsmtp.h"
#include "mail_json.hpp"
#include "msg_build.hpp"


using namespace std;


/**
 * main
 */
int main(void )
{

   struct MailParam p = getGmailParam();
    printMailParam( p );

    string SERVER = p.smtp_server;
    string PORT = to_string(p.smtp_port);
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


	string subject = "curlsmtp test";

	string message = getDefaultMessage();

	cout << message << endl;
	cout << endl;

	vector<string> to =
	{
		TO
	};

	vector<string> secret;
	vector<string> cc;
	vector<string> attach;

	CurlSmtp* mail = new CurlSmtp( 
		USER,
		PASSWD,
		to,
		secret,
		cc,
		attach,
		subject,
		message,
		SERVER,
		PORT );

	mail->send_mail();

	sleep(5);
	delete mail;

	return EXIT_SUCCESS;;
}


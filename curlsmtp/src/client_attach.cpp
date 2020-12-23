/**
 * curlsmtp sample
 * 2020-07-01 K.OHWADA
 */

// reference : https://github.com/honeyligo/curlsmtp/blob/master/main.cpp

// g++ src/client_attach.cpp src/curlsmtp.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp`


#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "curlsmtp.h"
#include "mail_json.hpp"
#include "msg_build.hpp"



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

    string SERVER = p.smtp_server;
    string PORT = to_string(p.smtp_port);
    string USER = p.user;
    string PASSWD = p.passwd;
    string FROM = p.from;
    string TO =  p.to;


	string subject = "curlsmtp attach";

	string message = getMessage();

	cout << message << endl;
	cout << endl;

	vector<string> to =
	{
		TO
	};

	string file( "data/baboon.png" );

	vector<string> attach =
	{
		file
	};

	vector<string> secret;
	vector<string> cc;

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

    mail->set_from(FROM);

	mail->send_mail();

	sleep(5);
	delete mail;

	return EXIT_SUCCESS;;
}


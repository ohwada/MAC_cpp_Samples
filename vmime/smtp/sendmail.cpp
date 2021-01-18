/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// send mail using sendmail command

// g++ sendmail.cpp -std=c++11 `pkg-config --cflags --libs vmime_json`  <br/>

// Requires
// You can use sendmail command


#include <iostream>
#include "smtp.hpp"

using namespace std;

// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  sendMessage
 */
bool sendMessage( 
vmime::shared_ptr <vmime::net::session> session, std::string smtp_url,  
vmime::shared_ptr <vmime::message> msg, 
bool verbose )
{

    if(verbose){
        std::cout << "url: " << smtp_url << std::endl;
  
    }

    vmime ::utility::url url( smtp_url );

    vmime::shared_ptr <vmime::net::transport> tr;	

			tr = session->getTransport(url);

	try {

		// Set the time out handler
		tr->setTimeoutHandlerFactory(vmime::make_shared <timeoutHandlerFactory>());

		// Connect to server
		tr->connect();

		// Send the message		
		tr->send(msg);
   
		tr->disconnect();

	} catch (vmime::exception& e) {

		std::cerr << std::endl;
		std::cerr << e << std::endl;
		return false;

	} catch (std::exception& e) {

		std::cerr << std::endl;
		std::cerr << "std::exception: " << e.what() << std::endl;
		return false;
	}

    return true;
}


/**
 *  main
 */
int main(void) 
{
    const	std::string  SUBJECT = "vmime sendmail";

    bool verbose = true;

    setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam( p );

    string FROM = p.from;
    string TO =  p.to;

    string URL = "sendmail://localhost";

    std::string body = getDefaultBody();
    vmime::shared_ptr <vmime::message> msg = buildMessage( SUBJECT, body, FROM, TO) ;

    printMessage( msg ) ;

    bool ret = sendMessage(  g_session, URL, msg, verbose ) ;

    if(ret){
    cout << "send mail successful" << endl;
	} else {
        cout << "send mail failed" << endl;
         return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}



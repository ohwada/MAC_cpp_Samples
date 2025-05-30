/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// recive mail from Gmail POP3 / IMAP server

#include <iostream>
#include <string>
#include <vector>
#include "pop3.hpp"
#include "plugin_certificateVerifier_gmail.hpp"

#include <glog/logging.h>

using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  main
 */
int main(int argc, char* argv[])
{

    bool verbose = true;

	int mode = getModeFromCommandLine(argc, argv);
	if(mode == -1){
        return EXIT_FAILURE;
    }

	int limit = getLimitFromCommandLine(argc, argv);

   setLocale("");

    MailParam  p = getGmailParam();
    printMailParam(p);
    string POP_URL = p.pop_url;
    string IMAP_URL = p.imap_url;
    string USER = p.user;
    string PASSWD = p.passwd;

	shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();

    bool ret = connectServer( mode, g_session, POP_URL, IMAP_URL, USER, PASSWD, cv, limit, verbose );

	if(!ret){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// C: Connecting to pop.gmail.com, port 995
// S: +OK Gpop ready for requests from


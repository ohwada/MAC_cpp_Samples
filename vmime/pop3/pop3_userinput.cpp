/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// recieve mail from POP3 / IMAP server
// user input username and password interactive

#include <iostream>
#include <string>
#include <vector>
#include "pop3.hpp"
#include "mail_json.hpp"
#include "certificateVerifier_nubntu.hpp"


using namespace std;


// Global session object
static vmime::shared_ptr <vmime::net::session> g_session = vmime::net::session::create();


/**
 *  main
 */
int main(int argc, char* argv[])
{

	const vmime::string POP3_URL = "pop3s://ubuntu";
	const vmime::string IMAP_URL = "imaps://ubuntu";

    bool verbose = true;

	cout << "vmime version: " << VMIME_VERSION << endl;

	int mode = getModeFromCommandLine(argc, argv);
	if(mode == -1){
        return EXIT_FAILURE;
    }

	int limit = getLimitFromCommandLine(argc, argv);

   setLocale("");

    MailParam  p = getUbuntuMailParam();
    printMailParam(p);
    string USER = p.user;

    // string PASSWD = p.passwd;
    string PASSWD = "";

	shared_ptr< vmime::security::cert::certificateVerifier > cv
= vmime::make_shared <customCertificateVerifier>();

    bool ret = connectServer( mode, g_session, POP3_URL, IMAP_URL, USER, PASSWD, cv, limit, verbose );

	if(!ret){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



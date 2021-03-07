/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// verify pop.gmail.com cert file
// test for certificateVerifier.hpp

// g++ test/test_certificateVerifier_gmail.cpp -std=c++11  `pkg-config --cflags --libs vmime`


#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "../pop3/plugin_certificateVerifier_gmail.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const std::string hostname("pop.gmail.com");

    const std::string filepath1 = "samples/certs/gmail/pop_gmail_com.pem";

    const std::string filepath2 = "samples/certs/gmail/GTS_CA_1O1.pem";

	customCertificateVerifier verifier;

	shared_ptr <vmime::security::cert::X509Certificate> cert1 
    = loadX509CertFromFile(filepath1);

	shared_ptr <vmime::security::cert::X509Certificate> cert2 
    = loadX509CertFromFile(filepath2);

	std::vector <shared_ptr <vmime::security::cert::certificate> > certs;
	certs.push_back(cert1);
	certs.push_back(cert2);

    shared_ptr <vmime::security::cert::certificateChain> chain
    = make_shared <vmime::security::cert::certificateChain>(certs);

	verifier.verify(chain, hostname);

    return EXIT_SUCCESS;
}


// load: gtsr1.pem
// load: gsr2.pem
// certificate succesful


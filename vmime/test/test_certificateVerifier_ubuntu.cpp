/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// verify ubuntu cert file
// test for certificateVerifier_ubuntu.hpp

// g++ test_certificateVerifier_ubuntu.cpp -std=c++11  `pkg-config --cflags --libs vmime`

#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "../pop3/certificateVerifier_ubuntu.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const std::string hostname("ubuntu");

    const std::string filepath = "data/sample_ubuntu.pem";

	customCertificateVerifier verifier;

	shared_ptr <vmime::security::cert::X509Certificate> cert 
    = loadX509CertFromFile(filepath);

	std::vector <shared_ptr <vmime::security::cert::certificate> > certs;
		certs.push_back(cert);

    shared_ptr <vmime::security::cert::certificateChain> chain
    = make_shared <vmime::security::cert::certificateChain>(certs);

	verifier.verify(chain, hostname);

    return EXIT_SUCCESS;
}


// certificate succesful



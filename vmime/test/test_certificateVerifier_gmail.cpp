/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// verify pop.gmail.com cert file
// test for certificateVerifier.hpp

// g++ test_certificateVerifier_ocn.cpp -std=c++11  `pkg-config --cflags --libs vmime`


// TODO
// certificate warning: Cannot verify certificate against trusted certificates.



#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "../pop3/certificateVerifier_gmail.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const std::string hostname("pop.gmail.com");

    const std::string filepath = "data/sample_pop.gmail.com.pem";

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


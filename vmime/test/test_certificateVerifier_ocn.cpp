/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// verify pop.ocn.ne.jp cert file
// test for certificateVerifier.hpp

// g++ test/test_certificateVerifier_ocn.cpp -std=c++11  `pkg-config --cflags --libs vmime`


#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "../pop3/plugin_certificateVerifier_ocn.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    const std::string hostname("pop.ocn.ne.jp");

    const std::string filepath1 = "samples/certs/ocn/pop_ocn_ne_jp.pem";

    const std::string filepath2 = "samples/certs/ocn/DigiCert_SHA2_Secure_Server_CA.pem";

    const std::string filepath3 = "samples/certs/ocn/DigiCert_Global_Root_CA.pem";

	customCertificateVerifier verifier;

	shared_ptr <vmime::security::cert::X509Certificate> cert1 
    = loadX509CertFromFile(filepath1);

	shared_ptr <vmime::security::cert::X509Certificate> cert2 
    = loadX509CertFromFile(filepath2);

	shared_ptr <vmime::security::cert::X509Certificate> cert3
    = loadX509CertFromFile(filepath3);

	std::vector <shared_ptr <vmime::security::cert::certificate> > certs;
		certs.push_back(cert1);
		certs.push_back(cert2);
		certs.push_back(cert3);

    shared_ptr <vmime::security::cert::certificateChain> chain
    = make_shared <vmime::security::cert::certificateChain>(certs);

	verifier.verify(chain, hostname);

    return EXIT_SUCCESS;
}


// load: DigiCert_Global_Root_CA.pem
// load: DigiCert_SHA2_Secure_Server_CA.pem
// certificate succesful 



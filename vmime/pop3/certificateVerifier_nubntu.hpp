/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// customCertificateVerifier for ubuntu

// original : https://github.com/kisli/vmime/blob/master/examples/example6_certificateVerifier.hpp

#if VMIME_HAVE_TLS_SUPPORT

#include <iostream>
#include <fstream>
#include "certificate_util.hpp"
#include "mail_directory.h"


// Certificate verifier (TLS/SSL)
class customCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier {

public:
	customCertificateVerifier() 
{
// ubuntu pem
	std::string filepath = getMailDir() + std::string( "/ubuntu.pem" );
	std::cout << "cert: " << filepath << std::endl;
	m_trustedCerts.push_back( loadX509CertificateFromFile( filepath ));
}

	void verify(
		const vmime::shared_ptr <vmime::security::cert::certificateChain>& chain,
		const vmime::string& hostname
	) {

	bool is_exception = false;
	std::string msg;

		try {

			setX509TrustedCerts(m_trustedCerts);

			defaultCertificateVerifier::verify(chain, hostname);

		} catch (vmime::security::cert::certificateNotTrustedException  ex1) {
				is_exception = true;
				msg = ex1.what();

		} catch (vmime::security::cert::certificateException ex2) {
				is_exception = true;
				msg = ex2.what();
		}

		if (is_exception ) {
				//disply message , if not verify
				std::cerr << "certificate warning: " <<  msg << std::endl;
				std::cerr << std::endl;
		} else {
				std::cout << "certificate succesful " << std::endl;
		}

	return;
} // verify

private:
	static std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> > m_trustedCerts;

};

std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> >
customCertificateVerifier::m_trustedCerts;

#endif // VMIME_HAVE_TLS_SUPPORT

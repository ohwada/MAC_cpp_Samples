/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// customCertificateVerifier
// save Certificate to file, if not verify

// original : https://github.com/kisli/vmime/blob/master/examples/example6_certificateVerifier.hpp

#if VMIME_HAVE_TLS_SUPPORT

#include <iostream>
#include <fstream>
#include "certificate_util.hpp"


// Certificate verifier (TLS/SSL)
class customCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier {

public:
// constrctor
	customCertificateVerifier() 
{

// get cert file list
	std::vector<std::string> vec;
	std::string error;
	
	bool ret = getFileList(".", "pem", vec, error);
	if(!ret){
		std::cout << error << std::endl;
		return;
	}

// inport cert files
	for(auto file: vec){
		std::cout << "import: " << file << std::endl;
		m_trustedCerts.push_back( loadX509CertificateFromFile( file ));
	}

}

// verify
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
				std::cerr << "certificate warning: " <<  msg << std::endl;
				std::cerr << std::endl;
		} else {
				std::cout << "certificate succesful " << std::endl;
				return;
		}

		// Obtain subject's certificate
		vmime::shared_ptr <vmime::security::cert::certificate> cert = chain->getAt(0);

		std::cout << std::endl;
		std::cout << "Server sent a '" << cert->getType() << "'" << " certificate." << std::endl;

		if (cert->getType() == "X.509") {

				vmime:: shared_ptr< vmime::security::cert::X509Certificate > x509cert = vmime::dynamicCast <vmime::security::cert::X509Certificate>(cert);

		// save
				std::string file;
				getTimestampFileName( "cert", "pem", file);
				saveX509CertificateFile( file, x509cert );
				std::cout << "saved to: " << file << std::endl;

		// always trust
				m_trustedCerts.push_back( x509cert  );
				setX509TrustedCerts(m_trustedCerts);
				defaultCertificateVerifier::verify(chain, hostname);
		}

	return;
} // verify

private:
	static std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> > m_trustedCerts;

};

std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> >
	customCertificateVerifier::m_trustedCerts;


#endif // VMIME_HAVE_TLS_SUPPORT

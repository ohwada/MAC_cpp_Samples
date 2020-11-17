#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// common CertificateVerifier
// save Certificate to file, if not verify

// original : https://github.com/kisli/vmime/blob/master/examples/example6_certificateVerifier.hpp


// reference : 
// A Developers Guide To VMime
// Certificate verification .
// https://www.vmime.org/public/documentation/book/vmime-book.pdf


#if VMIME_HAVE_TLS_SUPPORT

#include <iostream>
#include <fstream>
#include "certificate_util.hpp"


// Certificate verifier (TLS/SSL)
class commonCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier {

public:

/**
 * constractor
 */
	commonCertificateVerifier(void) 
{
	// dummy
}


/**
 * loadRootCAs
 */
void loadRootCAs(std::string dir)
{

	std::vector< vmime::shared_ptr < vmime::security::cert::X509Certificate > > certs;

	std::string error;

	bool ret = loadX509CertFromDir( dir, certs, error );

	if(ret){ 
			setX509RootCAs( certs );
	} else {
			std::cerr << "loadX509CertFromDir; " << error << std::endl;
	}

}


/**
 * loadTrustedCerts
 */
void loadTrustedCerts(std::string dir)
{

	std::vector< vmime::shared_ptr < vmime::security::cert::X509Certificate > > certs;

	std::string error;

	bool ret = loadX509CertFromDir(dir, certs, error );

	if(ret){ 
				setX509TrustedCerts( certs );
	} else {
				std::cerr << "loadX509CertFromDir; " << error << std::endl;
	}

}


/**
 * verifyCommon
 */
	void verifyCommon(
		const vmime::shared_ptr <vmime::security::cert::certificateChain>& chain,
		const vmime::string& hostname,
		bool is_save
	) 
{


	bool is_exception = false;

	std::string msg;

		try {

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

// X509 cert
				vmime:: shared_ptr< vmime::security::cert::X509Certificate > x509cert = vmime::dynamicCast <vmime::security::cert::X509Certificate>(cert);

			if(is_save) {

					// save cert file
					std::string file;
					std::string error;
					getTimestampFileName( "cert", "pem", file);

					bool ret = saveX509CertFile( file, x509cert, error );
					if(ret){
						std::cout << "saved to: " << file << std::endl;
					} else {
						std::cout << error << " : "<< file << std::endl;
					}
			}


	} // if Type "X.509"


	return;
}


};
// class commonCertificateVerifier end


#endif // VMIME_HAVE_TLS_SUPPORT

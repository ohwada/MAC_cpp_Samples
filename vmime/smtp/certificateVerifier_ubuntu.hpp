#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// customCertificateVerifier for ubuntu


// Preparation
// place Server Certificaton in Your home directory



#include "certificateVerifier.hpp"


class customCertificateVerifier : public commonCertificateVerifier {

public:
// constrctor
	customCertificateVerifier() 
{

// load ubuntu pem
	std::string filepath = getMailDir() + std::string( "/ubuntu.pem" );
	std::cout << "cert: " << filepath << std::endl;

	std::vector< vmime::shared_ptr < vmime::security::cert::X509Certificate > > certs;

	certs.push_back( loadX509CertFromFile( filepath ));

	setX509TrustedCerts( certs );

}
// constrctor end


// verify
	void verify(
		const vmime::shared_ptr <vmime::security::cert::certificateChain>& chain,
		const vmime::string& hostname
	) {

	verifyCommon( chain, hostname, true );

} 
// verify end

};
// class end

#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// customCertificateVerifier for OCN


// Preparation
// download Root Certificaton
// DigiCert Trusted Root Authority Certificates
// https://www.digicert.com/kb/digicert-root-certificates.htm


#include "plugin_certificateVerifier.hpp"

class customCertificateVerifier : public commonCertificateVerifier {

public:
// constrctor
	customCertificateVerifier() 
{

// Load root CAs
	std::string dir = getMailDir() + std::string( "/digicert" );

	loadRootCAs( dir );

// load Trusted Certs from current dir
	loadTrustedCerts( "." );

}
// constrctor end


// verify
	void verify(
		const vmime::shared_ptr <vmime::security::cert::certificateChain>& chain,
		const vmime::string& hostname
	) 
{

	verifyCommon( chain, hostname, true );

} 
// verify end


};
// class end

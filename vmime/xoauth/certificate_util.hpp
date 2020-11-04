#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

 // loadX509CertificateFromFile


// C  library
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// C++  library
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "vmime/vmime.hpp"
#include "file_util.hpp"


// prototype
vmime::shared_ptr <vmime::security::cert::X509Certificate> loadX509CertificateFromFile(const std::string filepath);
void saveX509CertificateFile(  std::string filepath, vmime:: shared_ptr< vmime::security::cert::X509Certificate > x509cert );


/** 
 *  loadX509CertificateFromFile
  */ 
vmime::shared_ptr <vmime::security::cert::X509Certificate> loadX509CertificateFromFile(const std::string filepath)
{
	std::ifstream ifs;
	ifs.open(filepath.c_str(), std::ios::in | std::ios::binary);
	if (!ifs) {
		std::cerr << "open faild: " << filepath << std::endl;
	}

	vmime::utility::inputStreamAdapter in(ifs);
	vmime::shared_ptr <vmime::security::cert::X509Certificate> cert ;
	cert = vmime::security::cert::X509Certificate::import(in); 

	return cert;
}


/** 
 *  saveX509CertificateFile
  */ 
void saveX509CertificateFile(  std::string filepath, vmime:: shared_ptr< vmime::security::cert::X509Certificate > x509cert )
{

	std::ofstream ofs;
	ofs.open(filepath.c_str(), std::ios::out | std::ios::binary);
	if (!ofs) {
		std::cerr << "open faild: " << filepath << std::endl;
	}

	vmime::utility::outputStreamAdapter out(ofs);
	x509cert->write( out, vmime::security::cert::X509Certificate::FORMAT_PEM );

}


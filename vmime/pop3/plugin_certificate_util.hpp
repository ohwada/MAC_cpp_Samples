#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

 // loadX509CertFromFile


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
#include "mail_directory.h"


// prototype
bool loadX509CertFromDir(std::string dir, std::vector< vmime::shared_ptr < vmime::security::cert::X509Certificate > > &certs );
vmime::shared_ptr <vmime::security::cert::X509Certificate> loadX509CertFromFile(const std::string filepath);
bool saveX509CertFile(  std::string filepath, vmime:: shared_ptr< vmime::security::cert::X509Certificate > x509cert, std::string &error );


/** 
 *  oadX509CertFromDir
  */ 
bool loadX509CertFromDir(std::string dir, std::vector< vmime::shared_ptr < vmime::security::cert::X509Certificate > > &certs, std::string &error ) 
{

	std::vector<std::string> vec;

	bool ret = getFileList(dir, "pem", vec, error);
	if(!ret){
        std::cerr << "getFileList: " << error << std::endl;
		return false;
	}

	for(auto file: vec){
		std::string fullpath = dir + std::string("/") + file;
		std::cout << "load: " << fullpath << std::endl;
		certs.push_back( loadX509CertFromFile( fullpath ) );
	}

	return true;
}


/** 
 *  loadX509CertFromFile
  */ 
vmime::shared_ptr <vmime::security::cert::X509Certificate>
 loadX509CertFromFile( const std::string filepath )
{
	std::ifstream ifs;

	ifs.open(filepath, std::ios::in | std::ios::binary);

	if (!ifs) {
        std::cerr << "can not open: " << filepath << std::endl;
		return NULL;
	}

    vmime::utility::inputStreamAdapter in(ifs);

	vmime::shared_ptr <vmime::security::cert::X509Certificate>  cert ;

	cert = vmime::security::cert::X509Certificate::import(in); 

    ifs.close();

	return cert;
}


/** 
 *  saveX509CertFile
  */ 
bool saveX509CertFile(  std::string filepath, vmime:: shared_ptr< vmime::security::cert::X509Certificate > cert, std::string &error )
{

	std::ofstream ofs;

	ofs.open( filepath, std::ios::out | std::ios::binary );

	if (!ofs) {
        error =  std::string("can not open: ");
		return false;
	}

	vmime::utility::outputStreamAdapter out(ofs);

	cert->write( out, vmime::security::cert::X509Certificate::FORMAT_PEM );

    ofs.close();

    return true;
}


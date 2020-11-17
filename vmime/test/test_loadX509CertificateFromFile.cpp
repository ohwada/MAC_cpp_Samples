/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// show CertificateFile
// test for certificate_util.hpp and loadX509CertificateFromFile

// g++ test_loadX509CertificateFromFile.cpp -std=c++11  `pkg-config --cflags --libs vmime`


#include <iostream>
#include <string>
#include "vmime/vmime.hpp"
#include "../pop3/certificate_util.hpp"

using namespace std;


/**
 *  getExpireDate
 */
void getExpireDate( 	shared_ptr <vmime::security::cert::X509Certificate> cert,  std::string &expire) 
{

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    vmime::datetime date = cert->getExpirationDate();
 
    int year = date.getYear();

    int month = date.getMonth();
 
    int day = date.getDay();
 
    int hour = date.getHour();
 
    int minute = date.getMinute();
 
    int second = date.getSecond();

    snprintf(buf, BUFSIZE, "%d-%d-%d %d:%d:%d", year, month, day, hour, minute, second);

    expire = std::string(buf);
}


/**
 * main
 */
int main(int argc, char* argv[])
{

    std::string file = "data/sample_pop.gmail.com.pem";

    if(argc == 2){
        file =  argv[1];
    } else {
        cout << "usage: " <<  argv[0] << " [file] " << endl;
    }



	shared_ptr <vmime::security::cert::X509Certificate> cert 
    = loadX509CertificateFromFile(file);
    if(cert == NULL) {
	    return EXIT_FAILURE;
    }

    std::string issuer = cert->getIssuerString();

    std::string expire;

    getExpireDate( cert, expire );

    std::cout <<  file << std::endl;

    std::cout  << "Issuer: " <<  issuer << std::endl;

    std::cout  << "Expire: " <<  expire << std::endl;

    return EXIT_SUCCESS;
}




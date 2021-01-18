/**
  * vmime sample
 * 2020-07-01 K.OHWADA
 */

// display version

// g++ version.cpp -std=c++11 `pkg-config --cflags --libs vmime` -lgnutls -lgsasl

#include <iostream>
#include "vmime/vmime.hpp"
#include <gsasl.h>
#include <gnutls/gnutls.h>

using namespace std;


/**
  * main
 */
int main(void)
{

    cout << "VMIME_VERSION: " <<  VMIME_VERSION << endl;

	cout << "libname: "<<  vmime::libname() << endl;
	cout << " libversion: "<<  vmime::libversion() << endl;
	cout << " libapi: "<<  vmime::libapi() << endl;


    printf( "libgsasl version: %s \n", 
    gsasl_check_version(NULL) );

    printf( "libgnutls version: %s \n", gnutls_check_version(NULL) );

    return EXIT_SUCCESS;
}


// VMIME_VERSION: 0.9.2
// libname: vmime
 // libversion: 0.9.2 (Aug 18 2020 14:31:13)
 // libapi: 1.0.0
// libgsasl version: 1.8.1 
// libgnutls version: 3.6.15


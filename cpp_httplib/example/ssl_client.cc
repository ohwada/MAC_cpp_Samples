/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS client

 // g++ ssl_client.cc -std=c++11 `pkg-config --cflags --libs openssl` -o client

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/client.cc

//
//  client.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "httplib.h"
#include "error.h"


/**
 *  cert file
 */
#define CA_CERT_FILE "cert/ca-bundle.crt"


using namespace std;


/**
 * main
 */
int main(void) 
{

const std::string HOST("localhost");

const char *PATH = "/hi";

const int PORT = 8081;

const bool VERYFY = false;

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  httplib::SSLClient cli(HOST, PORT);
  // httplib::SSLClient cli("google.com");
  // httplib::SSLClient cli("www.youtube.com");
  cli.set_ca_cert_path(CA_CERT_FILE);
  cli.enable_server_certificate_verification( VERYFY );
#else
  httplib::Client cli(HOST, PORT);
#endif

    auto res = cli.Get( PATH );

    if ( res ) {
        cerr << res->status << endl;
        cerr << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    } else {
        printError( res.error() );
    }

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
    auto result = cli.get_openssl_verify_result();
    if (result) {
      cout << "verify error: " << X509_verify_cert_error_string(result) << endl;
    }
#endif

    return EXIT_SUCCESS;
}


// 200
// text/html
// <h1>Hello World!</h1> '



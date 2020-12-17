/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS Client

 // g++ https/https_client.cpp -std=c++11 `pkg-config --cflags --libs openssl` -o client

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
#include "httplib_error.h"

using namespace std;


/**
 * main
 */
int main(int argc, const char *argv[]) 
{


    string file_ca_cert = "cert/ca-bundle.crt";

    string host = "example.com";

    int port = 443;

    string path = "/";

    bool is_verify = true;

    if (argc == 6) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
        path = argv[3]; 
        is_verify = (bool)atoi(argv[4]); 
        file_ca_cert = argv[5]; 
    } else if (argc == 5) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
        path = argv[3]; 
        is_verify = (bool)atoi(argv[4]); 
    } else if (argc == 4) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
        path = argv[3]; 
    } else if (argc == 3) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
    } else if (argc == 2) { 
        host = argv[1]; 
    } else {
        cerr << "usage: " << argv[0] << " [host] [port] [path] [verify] [file ca cert] " << endl;
    }

    cerr << "host: " << host << endl;
    cerr << "port: " << port << endl;
    cerr << "path: " << path << endl;
    cerr << boolalpha << "verify: " << is_verify << endl;
  cerr << "file_ca_cert: " << file_ca_cert << endl;

  httplib::SSLClient cli(host, port);
  cli.set_ca_cert_path( (char*)file_ca_cert.c_str() );
  cli.enable_server_certificate_verification( is_verify );

    auto res = cli.Get( (char*)path.c_str() );

    if ( res ) {
        cerr << endl;
        cerr << "Status: " << res->status << endl;
        cerr << "Content-Type: " << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    } else {
        printError( res.error() );
    }


    auto result = cli.get_openssl_verify_result();
    if (result) {
      cout << "verify error: " << X509_verify_cert_error_string(result) << endl;
    }


    return EXIT_SUCCESS;
}


// Status: 200
// Content-Type: text/html; charset=UTF-8
// <title>Example Domain</title>


/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS Server

// g++ https/https_server.cpp -std=c++11 `pkg-config --cflags --libs openssl` -o server

// original :  https://github.com/yhirose/cpp-httplib/blob/master/example/server.cc

//
//  sample.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "http_server.h"


using namespace std;


/**
 * main
 */
int main(int argc, const char *argv[]) 
{

    const char FILE_CERT[] = "certs/localhost_root_signed_cert.pem";

    const char FILE_KEY[] = "certs/localhost_key.pem";

    const char BASE_DIR2[] = "www2";

    int port = 8081;

    if (argc == 2) { 
        port = atoi(argv[1]); 
    } else {
        cout << "usage: " << argv[0] << " [port] " << endl;
    }

  httplib::SSLServer svr( FILE_CERT, FILE_KEY );

  if (!svr.is_valid()) {
        printf("server has an error...\n");
        return EXIT_FAILURE;
  }

  svr.set_error_handler( error_handler );

  svr.set_logger( logger );

  if ( !svr.set_mount_point("/", BASE_DIR2) ) {
        cout << "The specified base directory doesn't exist...";
        return EXIT_FAILURE;
  }


    cout << "The server started at port " << port << "..." << endl;

  svr.listen(LOCALHOST, port);

    return EXIT_SUCCESS;
}


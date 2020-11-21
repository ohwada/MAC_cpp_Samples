% /**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// simple HTTP client
// sccess to "http://localhost:8080"

// g++ simplecli.cc -std=c++11 -o cli
//  ./cli > simple.html

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/simplecli.cc

//
//  simplecli.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <iostream>
#include "httplib.h"
#include "error.h"


using namespace std;


/**
 * main
 */
int main(void) 
{

    const char *PATH = "/";

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  auto scheme_host_port = "https://localhost:8080";
#else
  auto scheme_host_port = "http://localhost:8080";
#endif

    httplib::Client client( scheme_host_port );
    auto res = client.Get( PATH );

    if ( res ) {
        cerr << res->status << endl;
        cerr << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    } else {
        printError( res.error();
    }

    return EXIT_SUCCESS;
}


//200
//text/html
//<html>
//<head>
//<title>cpphttplib demo</title>
//</head>
//<body>
//<h1>cpphttplib demo</h1>
//</body></html>
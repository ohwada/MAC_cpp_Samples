/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Client

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/simplecli.cc
//
//  simplecli.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <iostream>
#include "httplib.h"

using namespace std;


/**
 * main
 */
int main(int argc, const char *argv[]) 
{

    string host = "example.com";

    int port = 80;

    string path = "/";

    if (argc == 4) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
        path = argv[3]; 
    } else if (argc == 3) { 
        host = argv[1]; 
        port = atoi(argv[2]); 
    } else if (argc == 2) { 
        host = argv[1]; 
    } else {
        cerr << "usage: " << argv[0] << " [host] [port] [path] " << endl;
    }

    cerr << "host: " << host << endl;
    cerr << "port: " << port << endl;
    cerr << "path: " << path << endl;

    httplib::Client client( host, port );

    auto res = client.Get( path.c_str() );

    if ( res ) {
 v     cerr << endl;
        cerr << "Status: " << res->status << endl;
        cerr << "Content-Type: " << res->get_header_value("Content-Type") << endl;
        cout << res->body << endl;
    } else {
        printError( res.error() );
    }

    return EXIT_SUCCESS;
}


// Status: 200
// Content-Type: text/html; charset=UTF-8
//  <title>Example Domain</title>



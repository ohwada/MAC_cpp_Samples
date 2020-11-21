/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTP Server

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/simplesvr.cc
//
//  simplesvr.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//


#include <iostream>
#include "server.h"


using namespace std;


/**
 * main
 */
int main(int argc, const char *argv[]) 
{

    int port = 8080;

    if (argc == 2) { 
        port = atoi(argv[1]); 
    } else {
        cout << "usage: " << argv[0] << " [port] " << endl;
    }

  httplib::Server svr;

  svr.set_error_handler( error_handler );

  svr.set_logger( logger );

  if ( !svr.set_mount_point("/", BASE_DIR) ) {
        cout << "The specified base directory doesn't exist...";
        return EXIT_FAILURE;
  }

  cout << "The server started at port " << port << "..." << endl;

  svr.listen(LOCALHOST, port);


    return EXIT_SUCCESS;
}

/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// very simple HTTP server
// respnse "Hello World!"

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/hello.cc

//
//  hello.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <iostream>
#include "httplib.h"

using namespace httplib;


/**
 * main
 */
int main(void) 
{

    const char *HOST = "localhost";

    const int PORT = 8080;

  Server svr;

  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_content("<h1>Hello World!</h1>", "text/html");
  });

    svr.listen(HOST, PORT );

    std::cout << "listen: " << PORT << std::endl;

    return EXIT_SUCCESS;
}


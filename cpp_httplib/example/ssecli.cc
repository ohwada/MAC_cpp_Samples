/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// SSE (Server Send Event) client

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/ssecli.cc

//
//  ssecli.cc
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
int main(void) 
{

    const char *scheme_host_port ="http://localhost:1234";

// event1
  httplib::Client( scheme_host_port )
      .Get("/event1", [&](const char *data, size_t data_length) {
        std::cout << string(data, data_length);
        return true;
      });

    return EXIT_SUCCESS;
}

/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTP server with redirect

// https://github.com/yhirose/cpp-httplib/blob/master/example/redirect.cc

//
//  redirect.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//


#include "httplib.h"


/**
 * cert file
 */
#define SERVER_CERT_FILE "./cert.pem"
#define SERVER_PRIVATE_KEY_FILE "./key.pem"

using namespace httplib;


/**
 * main
 */
int main(void) 
{

    const char *HOST = "localhost";

    const int PORT_HTTP = 8080;

    const int PORT_HTTPS = 8081;

  // HTTP server
  Server http;

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  SSLServer https(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);
#endif

// test
  http.Get("/test", [](const Request & /*req*/, Response &res) {
    res.set_content("Test\n", "text/plain");
  });

  http.set_error_handler([](const Request & /*req*/, Response &res) {
// redirect to https
    res.set_redirect("https://localhost:8081/");
  });

  // HTTPS server
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT

// access to root ("/") : redirect to hi
  https.Get("/", [=](const Request & /*req*/, Response &res) {
    res.set_redirect("/hi");
  });

// hi
  https.Get("/hi", [](const Request & /*req*/, Response &res) {
    res.set_content("Hello World!\n", "text/plain");
  });

// stop
  https.Get("/stop", [&](const Request & /*req*/, Response & /*res*/) {
    https.stop();
    http.stop();
  });

#endif


  // Run servers
  auto httpThread = std::thread([&]() { http.listen( HOST, PORT_HTTP ); });

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  auto httpsThread = std::thread([&]() { https.listen( HOST, PORT_HTTPS ); });
#endif

// stop http thread
  httpThread.join();

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
// stop https thread
  httpsThread.join();
#endif

    return EXIT_SUCCESS;
}


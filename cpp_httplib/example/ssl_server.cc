/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTPS server

// g++ ssl_server.cc -std=c++11 `pkg-config --cflags --libs openssl` -o server

// original :  https://github.com/yhirose/cpp-httplib/blob/master/example/server.cc

//
//  sample.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <chrono>
#include <cstdio>
#include "httplib.h"


/**
 *  cert file
 */
#define SERVER_CERT_FILE "cert/server.pem"
#define SERVER_PRIVATE_KEY_FILE "cert/server.key"

using namespace httplib;


/**
 * dump_headers
 */
std::string dump_headers(const Headers &headers) {
  std::string s;
  char buf[BUFSIZ];

  for (auto it = headers.begin(); it != headers.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}


/**
 * log
 */
std::string log(const Request &req, const Response &res) {
  std::string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  std::string query;
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%c%s=%s",
             (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
             x.second.c_str());
    query += buf;
  }
  snprintf(buf, sizeof(buf), "%s\n", query.c_str());
  s += buf;

  s += dump_headers(req.headers);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
  s += buf;
  s += dump_headers(res.headers);
  s += "\n";

  if (!res.body.empty()) { s += res.body; }

  s += "\n";

  return s;
}


/**
 * main
 */
int main(void) 
{

    const char *HOST = "localhost";

    const int PORT = 8081;

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  SSLServer svr(SERVER_CERT_FILE, SERVER_PRIVATE_KEY_FILE);
#else
  Server svr;
#endif

  if (!svr.is_valid()) {
        printf("server has an error...\n");
        return EXIT_FAILURE;
  }

// access to root ("/") : redirect to hi
  svr.Get("/", [=](const Request & /*req*/, Response &res) {
    res.set_redirect("/hi");
  });

// access to hi : return response "hello"
  svr.Get("/hi", [](const Request & /*req*/, Response &res) {
    res.set_content("<h1>Hello World!</h1> \n", "text/html");
  });

// access to slow : 
// wait 2 secondes and return response "slow"
  svr.Get("/slow", [](const Request & /*req*/, Response &res) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    res.set_content("<b>Slow...</b> \n", "text/html");
  });

// access to dump : dump header
  svr.Get("/dump", [](const Request &req, Response &res) {
    res.set_content(dump_headers(req.headers), "text/plain");
  });

// access to stop : stop server
  svr.Get("/stop", [&](const Request  /*req*/, Response &res /*res*/) { 
        res.set_content("<b>Goodby</b> \n", "text/html");
        svr.stop(); 
        printf("debug: stop server \n"); 
        });

  svr.set_error_handler([](const Request & /*req*/, Response &res) {
    const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
    char buf[BUFSIZ];
    snprintf(buf, sizeof(buf), fmt, res.status);
    res.set_content(buf, "text/html");
  });

  svr.set_logger([](const Request &req, const Response &res) {
    printf("%s", log(req, res).c_str());
  });

  svr.listen(HOST, PORT);

    return EXIT_SUCCESS;
}

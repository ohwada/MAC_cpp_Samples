#pragma once
/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// funtion for HTTP Server

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/simplesvr.cc
//
//  simplesvr.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <iostream>
#include <string>
#include <cstdio>
#include "httplib.h"


// constant
const size_t BUFSIZE = 512;
const char LOCALHOST[] = "localhost";
const char BASE_DIR[] = "www";


// prototype
std::string dump_headers(const httplib::Headers &headers) ;
std::string dump_multipart_files(const httplib::MultipartFormDataMap &files);
std::string log(const httplib::Request &req, const httplib::Response &res) ;
void error_handler( const httplib::Request &req, httplib::Response &res ) ;
void logger( const httplib::Request &req, const httplib::Response &res);


/**
 *  dump_headers
 */
std::string dump_headers(const httplib::Headers &headers) 
{
  std::string s;
  char buf[BUFSIZE];

  for (const auto &x : headers) {
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}


/**
 * dump_multipart_files
 */
std::string dump_multipart_files(const httplib::MultipartFormDataMap &files) 
{
  std::string s;
  char buf[BUFSIZE];

  s += "--------------------------------\n";

  for (const auto &x : files) {
    const auto &name = x.first;
    const auto &file = x.second;

    snprintf(buf, sizeof(buf), "name: %s\n", name.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "filename: %s\n", file.filename.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "content type: %s\n", file.content_type.c_str());
    s += buf;

    snprintf(buf, sizeof(buf), "text length: %zu\n", file.content.size());
    s += buf;

    s += "----------------\n";
  }

  return s;
}


/**
 * log
 */
std::string log(const httplib::Request &req, const httplib::Response &res) 
{
  std::string s;
  char buf[BUFSIZE];

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
  s += dump_multipart_files(req.files);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d\n", res.status);
  s += buf;
  s += dump_headers(res.headers);

  return s;
}



/**
 * error_handler
 */
void error_handler( const httplib::Request &req, httplib::Response &res ) 
{

    const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";

    char buf[BUFSIZE];

    snprintf(buf, sizeof(buf), fmt, res.status);

    res.set_content(buf, "text/html");
}


/**
 * logger
 */
void logger( const httplib::Request &req, const httplib::Response &res) 
{
    std::cout << log(req, res); 
}

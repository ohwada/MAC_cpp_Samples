#pragma once
/**
 * http_request_builder.hpp
 * 2022-06-01 K.OHWADA
 */

#include <string>
#include <boost/format.hpp>


// constant
const std::string ROOT_PATH = "/";


// prototype
std::string build_http_request(std::string host, std::string path);


/** 
 *  build_http_request
 */
std::string build_http_request(std::string host, std::string path)
{

 const std::string HEADER_ACCEPT_ALL(
"Accept: */* \r\n");

const std::string HEADER_CLOSE(
"Connection: close\r\n");

const std::string CRLF("\r\n");

// Do not put spaces after HTTP/1.1 
 const std::string FORMAT_GET(
"GET %s HTTP/1.1\r\n");

 const std::string FORMAT_HOST(
"Host: %s\r\n");


std::string hdr_get = 
boost::str( boost::format(FORMAT_GET) % path);

std::string hdr_host = 
boost::str( boost::format(FORMAT_HOST) % host);

    std::string request = 
    hdr_get
    + hdr_host
    + HEADER_ACCEPT_ALL
    +  HEADER_CLOSE
    + CRLF;

    return request;
}


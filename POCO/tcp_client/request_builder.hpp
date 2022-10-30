#pragma once
/**
 * request_builder.hpp
 * 2022-06-01 K.OHWADA
 */


#include <string>
#include "Poco/Format.h"

// constant
const Poco::UInt16 PORT_HTTP = 80;

const std::string ROOT_PATH("/");


// prototype
std::string build_http_root_path_request(std::string host);
std::string build_http_request(std::string host, std::string path);


/** 
 *  build_http_root_path_request
 */
std::string build_http_root_path_request(std::string host)
{
    return build_http_request( host, ROOT_PATH);
}


/** 
 *  build_http_request
 */
std::string build_http_request(std::string host, std::string path)
{

    const std::string HEADER_ACCEPT_ALL("Accept: */* \r\n");

    const std::string HEADER_CLOSE("Connection: close\r\n\r\n");

// Dont put space after HTTP/1.1 
    const std::string FORMAT_GET("GET %s HTTP/1.1\r\n");

    const std::string FORMAT_HOST("Host: %s\r\n");


    std::string hdr_get;
    Poco::format(hdr_get, FORMAT_GET,  path);

    std::string hdr_host;
    Poco::format( hdr_host, FORMAT_HOST, host );

    std::string request = hdr_get
    + HEADER_ACCEPT_ALL
    + hdr_host
    + HEADER_CLOSE;

    return request;
}


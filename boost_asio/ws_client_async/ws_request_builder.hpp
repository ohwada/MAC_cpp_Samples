#pragma once
/**
 * ws_request_builder.hpp
 * 2022-10-01 K.OHWADA
 */

#include <string>
#include <boost/format.hpp>
#include "random_string.hpp"
#include "base64.hpp"


// prototype
std::string build_ws_request(std::string host, std::string path, std::string key);
std::string gen_ws_sec_key(size_t size);


/** 
 *  gen_ws_key
 */
std::string gen_ws_sec_key(size_t size)
{
    auto rand_key = genRandomStringMix(size);

    return encode_base64_str(rand_key);
}


/** 
 *  build_http_request
 */
std::string build_ws_request(std::string host, std::string path, std::string key)
{

    const std::string HDR_UPGRAGE(
"Upgrade: websocket\r\n");

    const std::string HDR_CONNECTION(
"Connection: upgrade\r\n");

    const std::string HDR_VERSION(
"Sec-WebSocket-Version: 13\r\n");

    const std::string CRLF("\r\n");

// Do not put spaces after HTTP/1.1 
 const std::string FORMAT_GET(
"GET %s HTTP/1.1\r\n");

 const std::string FORMAT_HOST(
"Host: %s\r\n");
    const std::string FORMAT_SEC_KEY(
"Sec-WebSocket-Key: %s\r\nSec");

    std::string hdr_get = 
boost::str( boost::format(FORMAT_GET) % path);

    std::string hdr_host = 
boost::str( boost::format(FORMAT_HOST) % host);

    std::string hdr_key = 
boost::str( boost::format(FORMAT_SEC_KEY) % key);


    std::string request = 
    hdr_get
    + hdr_host
    + HDR_UPGRAGE
    +  HDR_CONNECTION
    + hdr_key
    + HDR_VERSION
    + CRLF;

    return request;
}


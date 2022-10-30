/**
 * test_server_client.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <cassert>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Thread.h>
#include <boost/format.hpp>
#include "poco_tcp_client.hpp"
#include "poco_file_stream.hpp"
#include "response_parser.hpp"
#include "config.hpp"


/**
 * main
 */
int main() 
{

 std::string fpath("sample/sample_server_request.txt");

std::string expect = R"(<html><head></head><body><h1>Local Server</h1><font size="+2">code<br/>|4/0dummy-code| <br/>scope<br/>|dummy-scope|<br/></font></body></html>)";

size_t data_size;

  std::string data = file_binary_read( fpath, data_size);

std::cout << data << std::endl;

    std::string host = "localhost";

std::string response;

tcp_client( host,  PORT, data,  response);

std::cout << "response" << std::endl;
std::cout << response << std::endl;

std::string header;
std::string body;

split_header_body(response, header, body);

std::cout << "body" << std::endl;
std::cout << body << std::endl;

    assert(body == expect);

    std::cout << "successful" << std::endl;

    return 0;
}



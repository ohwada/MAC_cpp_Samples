#pragma once
/**
 * pico_tcp.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <Poco/Net/Socket.h>

// prototype
void tcp_send(Poco::Net::StreamSocket &ss, std::string str);
std::string tcp_read(Poco::Net::StreamSocket &ss);


const int BYTE_LENGTH = 1024;


/**
 *  tcp_send
 */
void tcp_send(Poco::Net::StreamSocket &ss, std::string str)
{
    if (str.size() > BYTE_LENGTH) throw std::invalid_argument("str.size() > BYTE_LENGTH");
    int ret = ss.sendBytes(str.c_str(), str.size());
    if (ret < 0) throw std::exception();
}


/**
 *  tcp_read
 */
std::string tcp_read(Poco::Net::StreamSocket &ss)
{
    char data[BYTE_LENGTH];
    int count = ss.receiveBytes(data, BYTE_LENGTH);
    std::string str(data, count);
    if (count == BYTE_LENGTH) throw std::exception();
    return str;
}

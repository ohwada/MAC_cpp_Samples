#pragma once
/**
 * tcp.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <Poco/Net/Socket.h>

// prototype
void tcp_send(Poco::Net::StreamSocket &ss, std::string str);
std::string tcp_read(Poco::Net::StreamSocket &ss);

const int SEND_BYTE_LENGTH = 1024;
const int RECV_BYTE_LENGTH = 2048;

/**
 *  tcp_send
 */
void tcp_send(Poco::Net::StreamSocket &ss, std::string str)
{
    if (str.size() > SEND_BYTE_LENGTH) throw std::invalid_argument("str.size() > SEND_BYTE_LENGTH");
    int ret = ss.sendBytes(str.c_str(), str.size());
    if (ret < 0) {
        throw std::runtime_error("sendBytes faild");
    }
}


/**
 *  tcp_read
 */
std::string tcp_read(Poco::Net::StreamSocket &ss)
{
    char data[RECV_BYTE_LENGTH];
    int count = ss.receiveBytes(data, RECV_BYTE_LENGTH);
    std::string str(data, count);
    if (count == RECV_BYTE_LENGTH) {
        throw std::runtime_error("recieve buffer size is small");
    }
    return str;
}

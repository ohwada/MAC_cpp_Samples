#pragma once
/**
 * tcp.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://phst.hateblo.jp/entry/2016/10/20/131738

#include <iostream>
#include <string>
#include <Poco/Net/Socket.h>

// prototype
void tcp_send(Poco::Net::StreamSocket &ss, std::string str);
std::string tcp_read(Poco::Net::StreamSocket &ss);
std::string tcp_block_read(Poco::Net::StreamSocket &ss, size_t block_size, int loop, bool is_verbose);

const int SEND_BYTE_LENGTH = 1024;
const int RECV_BYTE_LENGTH = 1024;


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


/** 
 *  tcp_block_read
* ivide into small blocks and receive multiple times
 */
std::string tcp_block_read(Poco::Net::StreamSocket &ss, size_t block_size, int loop, bool is_verbose)
{

    const char NUL = '\0';

    std::string result;

    char buf[block_size+1];
    
    int i = 0;

    for(i=0; i<loop; i++)
    {
        std::memset(buf, NUL, block_size);
        int count = ss.receiveBytes(buf,  block_size);
        if( is_verbose ){
            std::cout << i << ": " << count << std::endl;
        }
        if(count == 0){
            break;
        }
        std::string str(buf, count);
        result += str;
    } // for

    std::cout << "loop: " << i << std::endl;
  
     return result;
}

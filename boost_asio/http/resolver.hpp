#pragma once
/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// resolve IP Address from hostname

// reference : https://stackoverflow.com/questions/31314433/how-do-i-convert-a-host-name-in-to-a-boost-address-or-endpoint

#include <string>
#include <boost/asio.hpp>

//prototype
bool get_ipaddress(std::string host, std::string &ipaddr, std::string &error);
bool get_address(std::string host, boost::asio::ip::address &address, std::string &error);
bool get_endpoint(std::string host, std::string service,   boost::asio::ip::tcp::endpoint &endpoint, std::string &error);


/**
 * get_ipaddress
 */
bool get_ipaddress(std::string host, std::string &ipaddr, std::string &error)
{

    boost::asio::ip::address address;

    bool ret = get_address( host, address, error );

    if(!ret){
        return false;
    }

    ipaddr = address.to_string();

    return true;
}


/**
 * get_address
 */
bool get_address(std::string host, boost::asio::ip::address &address, std::string &error)
{
    const std::string SERVICE("");

    boost::asio::ip::tcp::endpoint endpoint;

    bool ret = get_endpoint( host, SERVICE, endpoint, error );
    if(!ret){
        return ret;
    }

    address = endpoint.address();

    return true;
}


/**
 * get_endpoint
 */
bool get_endpoint(std::string host, std::string service,   boost::asio::ip::tcp::endpoint &endpoint, std::string &error)
{

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, service);

    bool is_error = false;
    try {
        boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
        endpoint = iter->endpoint();

    } catch ( boost::system::system_error &err ){
        is_error = true;
        error = err.what();
    }

    return !is_error;
}

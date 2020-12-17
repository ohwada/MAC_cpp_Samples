#pragma once
/**
 * boost sample
 * 2020-07-01 K.OHWADA
 */

// function for boost asio socket

#include <string>
#include <boost/asio.hpp>


// prototype
bool  asio_write_with_lf(boost::asio::ip::tcp::socket &socket, std::string msg, std::string &error); 
bool  asio_write(boost::asio::ip::tcp::socket &socket, std::string msg, std::string &error) ;
 bool asio_read_until_lf(boost::asio::ip::tcp::socket &socket, std::string &data, std::string &error);


// golobal
const char LF = '\n';


/**
 * asio_write_with_lf
 */
bool  asio_write_with_lf(boost::asio::ip::tcp::socket &socket, std::string msg, std::string &error) 
{

    std::string send_msg = msg + LF;

    return asio_write(socket,  send_msg, error) ;

}


/**
 * asio_write
 */
bool  asio_write(boost::asio::ip::tcp::socket &socket, std::string msg, std::string &error) 
{

try {
    std :: size_t size = boost::asio::write( socket, boost::asio::buffer(msg) );
} catch( const boost::system::system_error& ex ) {
        error = ex.what();
        return false;
}

    return true;
}


/**
 * asio_read_until_lf
 */
 bool asio_read_until_lf(boost::asio::ip::tcp::socket &socket, std::string &data, std::string &error) 
{

    boost::asio::streambuf buf;

try {
    std::size_t size = boost::asio::read_until( socket, buf, LF);
    data = boost::asio::buffer_cast<const char*>(buf.data());
} catch( const boost::system::system_error& ex ) {
        error = ex.what();
        return false;
}

    return true;
}


#pragma once
/**
 *  tcp_echo_client_async.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/async_client.cpp

#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>


// prototype
bool echo_client(std::string server, std::string port);
 std::string get_write_data();


/**
 *  class echo_client
 */
class echo_client
{
public:
/**
 * echo_client
 */
 echo_client(boost::asio::io_context& io_context,
      const std::string& server, const std::string& port)
    : resolver_(io_context),
      socket_(io_context)
  {
     resolver_.async_resolve(server, port,
        boost::bind(&echo_client::handle_resolve, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::results));
  }

private:
/**
 *  handle_resolve
 */
  void handle_resolve(const boost::system::error_code& err,
      const boost::asio::ip::tcp::resolver::results_type& endpoints)
  {
    std::cout << "handle_resolve" << std::endl;
    if (!err)
    {
      boost::asio::async_connect(socket_, endpoints,
          boost::bind(&echo_client::handle_connect, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }


/**
 *  handle_connect
 */
  void handle_connect(const boost::system::error_code& err)
  {
    std::cout << "handle_connect" << std::endl;
    if (!err)
    {
    
        auto write_data = get_write_data();

      boost::asio::async_write(socket_,  
   boost::asio::buffer(write_data),
          boost::bind(&echo_client::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

/**
 *  handle_read
 */
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
        std::string read(m_data,  bytes_transferred);
        std::cout << "r: " << read << std::endl;

        auto write_data = get_write_data();

        if( write_data.size() > 0) {
            boost::asio::async_write(socket_,
            boost::asio::buffer(write_data),
            boost::bind(&echo_client::handle_write, this,
            boost::asio::placeholders::error));
        }
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle_write
 */
  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(m_data, max_length),
          boost::bind(&echo_client::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

private:
  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::ip::tcp::socket socket_;
    boost::asio::io_context m_io_context;

  enum { max_length = 1024 };
  char m_data[max_length];
};


/**
 * echo_client
 */
bool echo_client(std::string server, std::string port)
{
  try
  {

    boost::asio::io_context io_context;

   class echo_client c(io_context, server, port);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
    return false;
  }

    return true;
}

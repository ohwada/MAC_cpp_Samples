#pragma once
/**
 *  ws_client_async.hpp
 * 2022-10-01 K.OHWADA
 */

// https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/async_client.cpp

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include  "ws_request_builder.hpp"
#include  "ws_frame_common.hpp"


// prototype
bool ws_client_async(std::string server, std::string port, std::string path);
std::vector<char> do_handle_read(char* data,  size_t bytes_transferred);


/**
 *  class ws_client
 */
class ws_client
{
public:
  ws_client(boost::asio::io_context& io_context,
      const std::string& server, const std::string& port, const std::string& path)
    : resolver_(io_context),
      socket_(io_context)
  {
    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    auto sec_key = gen_ws_sec_key(10);
    auto str_request = build_ws_request(server, path, sec_key);
    std::cout << "request" << std::endl;
    std::cout << str_request << std::endl;

    std::ostream request_stream(&request_);
    request_stream << str_request;

    // Start an asynchronous resolve to translate the server and service names
    // into a list of endpoints.
    resolver_.async_resolve(server, port,
        boost::bind(&ws_client::handle_resolve, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::results));
  }

private:
  void handle_resolve(const boost::system::error_code& err,
      const boost::asio::ip::tcp::resolver::results_type& endpoints)
  {
    if (!err)
    {
      // Attempt a connection to each endpoint in the list until we
      // successfully establish a connection.
      boost::asio::async_connect(socket_, endpoints,
          boost::bind(&ws_client::handle_connect, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

  void handle_connect(const boost::system::error_code& err)
  {
    if (!err)
    {
    
      // The connection was successful. Send the request.
      boost::asio::async_write(socket_,  request_,
          boost::bind(&ws_client::handle_write_request, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

  void handle_write_request(const boost::system::error_code& err)
  {
    if (!err)
    {
    socket_.async_read_some(boost::asio::buffer(m_data, max_length),
        boost::bind(&ws_client::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
        auto write_data = do_handle_read(m_data,  bytes_transferred);
        auto write_data_size = write_data.size();

        if(write_data_size > 0) {
            dump_write_vec(write_data);
            boost::asio::async_write(socket_,
            boost::asio::buffer( (char *)write_data.data(), write_data_size),
            boost::bind(&ws_client::handle_write, this,
            boost::asio::placeholders::error));
        } else {
// recurcive call myself
            socket_.async_read_some(boost::asio::buffer(m_data, max_length),
            boost::bind(&ws_client::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(m_data, max_length),
          boost::bind(&ws_client::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  enum { max_length = 1024 };
  char m_data[max_length];
  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf request_;
};


/**
 *  ws_client_async
 */
bool ws_client_async(std::string server, std::string port, std::string path)
{
  try
  {

    boost::asio::io_context io_context;
    ws_client c(io_context, server, port, path);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
    return false;
  }

    return true;
}

#pragma once
/**
 *  http_client_async.hpp
 * 2022-10-01 K.OHWADA
 */

// https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/async_client.cpp

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include  "http_request_builder.hpp"


// prototype
bool http_client_async(std::string server, std::string port, std::string path);


/**
 *  class http_client
 */
class http_client
{
public:
  http_client(boost::asio::io_context& io_context,
      const std::string& server, const std::string& port, const std::string& path)
    : resolver_(io_context),
      socket_(io_context)
  {
    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    std::string str_request = build_http_request(server, path);
    std::cout << "request" << std::endl;
    std::cout << str_request << std::endl;

    std::ostream request_stream(&request_);
    request_stream << str_request;

    // Start an asynchronous resolve to translate the server and service names
    // into a list of endpoints.
    resolver_.async_resolve(server, port,
        boost::bind(&http_client::handle_resolve, this,
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
          boost::bind(&http_client::handle_connect, this,
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
          boost::bind(&http_client::handle_write_request, this,
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
      // Read the response status line. The response_ streambuf will
      // automatically grow to accommodate the entire line. The growth may be
      // limited by passing a maximum size to the streambuf constructor.
      boost::asio::async_read_until(socket_, response_, "\r\n",
          boost::bind(&http_client::handle_read_status_line, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }

  void handle_read_status_line(const boost::system::error_code& err)
  {
std::cout << "handle_read_status_line" << std::endl;

    if (!err)
    {
      // Check that response is OK.
      std::istream response_stream(&response_);
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;
      std::getline(response_stream, status_message);

    std::cout << std::endl;
    std::cout << "response" << std::endl;
std::cout << "http_version: " <<  http_version << std::endl;
std::cout << "status_code: " <<  status_code << std::endl;
std::cout << "status_message: " <<  status_message << std::endl;

      if (!response_stream || http_version.substr(0, 5) != "HTTP/")
      {
        std::cout << "Invalid response\n";
        return;
      }
      if (status_code != 200)
      {
        std::cout << "Response returned with status code ";
        std::cout << status_code << "\n";
        return;
      }

      // Read the response headers, which are terminated by a blank line.
      boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
          boost::bind(&http_client::handle_read_headers, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err << "\n";
    }
  }

  void handle_read_headers(const boost::system::error_code& err)
  {
std::cout << "handle_read_headers" << std::endl;

    if (!err)
    {
      // Process the response headers.
      std::istream response_stream(&response_);

      std::string header;
      while (std::getline(response_stream, header) && header != "\r") {
        std::cout << header << "\n";
        } // while
      std::cout << "\n";

      // Write whatever content we already have to output.
      if (response_.size() > 0){
        std::cout << &response_;
}

      // Start reading remaining data until EOF.
      boost::asio::async_read(socket_, response_,
          boost::asio::transfer_at_least(1),
          boost::bind(&http_client::handle_read_content, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << err << "\n";
    }
  }

  void handle_read_content(const boost::system::error_code& err)
  {
std::cout << "handle_read_content" << std::endl;

    if (!err)
    {
      // Write all of the data that has been read so far.
      std::cout << &response_;

      // Continue reading remaining data until EOF.
      boost::asio::async_read(socket_, response_,
          boost::asio::transfer_at_least(1),
          boost::bind(&http_client::handle_read_content, this,
            boost::asio::placeholders::error));
    }
    else if (err != boost::asio::error::eof)
    {
      std::cout << "Error: " << err << "\n";
    }
  }

  boost::asio::ip::tcp::resolver resolver_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf request_;
  boost::asio::streambuf response_;
    boost::asio::io_context m_io_context;
};


/**
 *  http_client_async
 */
bool http_client_async(std::string server, std::string port, std::string path)
{
  try
  {

    boost::asio::io_context io_context;
    http_client c(io_context, server, port, path);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
    return false;
  }

    return true;
}

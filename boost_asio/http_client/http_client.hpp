/**
 * http_client.hpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/http/client/sync_client.cpp


#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>

// prototype
bool http_client(std::string host, std::string request, std::string &body,  bool is_verbose);


using boost::asio::ip::tcp;


/**
 *  http_client
 */
bool http_client(std::string host, std::string request_data, std::string &body,    bool is_verbose)
{
  try
  {
    boost::asio::io_context io_context;

    // Get a list of endpoints corresponding to the server name.
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve(host, "http");

    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << request_data;
    
    // Send the request.
    boost::asio::write(socket, request);

    // Read the response status line. The response streambuf will automatically
    // grow to accommodate the entire line. The growth may be limited by passing
    // a maximum size to the streambuf constructor.
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // Check that response is OK.
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return false;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code " << status_code << "\n";
      return false;
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // Process the response headers.

    if (is_verbose ){
      std::cout << std::endl;
      std::cout << "header" << std::endl;
    }

    std::string header;
    while (std::getline(response_stream, header) && header != "\r") {
        if (is_verbose ){
            std::cout << header << "\n";
        }
    } // while

    if (is_verbose ){
        std::cout << "\n";
    }

    std::ostringstream oss;

    // Write whatever content we already have to output.
    if (response.size() > 0){
        oss << &response;
    }

    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(socket, response,
          boost::asio::transfer_at_least(1), error)) {
      oss << &response;
    } // while
    body = oss.str();
    if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
      return false;
  }

  return true;
}

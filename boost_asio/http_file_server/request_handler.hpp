/**
 * request_handler.hpp
 * 2022-06-01 K.OHWADA
 */

// original: https://github.com/boostorg/asio/blob/develop/example/cpp03/http/server/request_handler.hpp

//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/format.hpp>


/**
 * http server
 */
namespace http {
namespace server {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit request_handler(const std::string& doc_root);

  /// Handle a request and produce a reply.
  void handle_request(const request& req, reply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace server
} // namespace http


// prototype
void on_request(const http::server::request& req, http::server::reply& rep, std::string doc_root, std::string request_path);
void do_response_text(http::server::reply& rep, std::string text, std::string mime);
void do_response_file(http::server::reply& rep, std::string full_path);
std::string get_extension(std::string fpath);
void do_response_not_found(http::server::reply& rep, std::string request_path);
std::string build_msg_not_found( std::string request_path);
bool can_open(std::string full_path);


#endif // HTTP_REQUEST_HANDLER_HPP

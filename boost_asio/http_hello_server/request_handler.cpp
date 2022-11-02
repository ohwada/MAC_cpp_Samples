/**
 * request_handler.cpp
 * 2022-06-01 K.OHWADA
 */

// original: https://github.com/boostorg/asio/blob/develop/example/cpp03/http/server/request_handler.cpp


#include "request_handler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"


/**
 *  do_response_text
 */
void do_response_text(http::server::reply& rep, std::string text, std::string mime)
{
    size_t text_size = text.size();
    std::string length = std::to_string(text_size);

  // Fill out the reply to be sent to the client.
    rep.status = http::server::reply::ok;
    rep.content = text;
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = length;
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime;
}


/**
 *  do_response_file
 */
void do_response_file(http::server::reply& rep, std::string full_path)
{

    std::string extension = get_extension(full_path);
    std::cout << "ext: " << extension << std::endl;

// Open the file to send back.
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
        std::cerr << "cannot open: " << full_path << std::endl;
        return;
  }

  // Fill out the reply to be sent to the client.
    rep.status = http::server::reply::ok;
    char buf[512];
    while (is.read(buf, sizeof(buf)).gcount() > 0){
        rep.content.append(buf, is.gcount());
    } // while
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = http::server::mime_types::extension_to_type(extension);
}


/**
 *  get_extension
 */
std::string get_extension(std::string fpath)
{
  // Determine the file extension.
    std::size_t last_slash_pos = fpath.find_last_of("/");
    std::size_t last_dot_pos = fpath.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
    {
        extension = fpath.substr(last_dot_pos + 1);
    }
    return extension;
}


/**
 *  http server
 */
namespace http {
namespace server {

request_handler::request_handler(const std::string& doc_root)
  : doc_root_(doc_root)
{
}


void request_handler::handle_request(const request& req, reply& rep)
{

  // Decode url to path.
  std::string request_path;
  if (!url_decode(req.uri, request_path))
  {
    rep = reply::stock_reply(reply::bad_request);
    return;
  }


  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || request_path.find("..") != std::string::npos)
  {
    rep = reply::stock_reply(reply::bad_request);
    return;
  }

    on_request(req, rep, request_path);
}


bool request_handler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server
} // namespace http

#pragma once
/**
 * response_builder.hpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/boostorg/beast/blob/develop/example/http/server/sync/http_server_sync.cpp

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>

namespace http = beast::http;           // from <boost/beast/http.hpp>


// prototype
http::response<http::string_body> build_string_response(std::string text,  beast::string_view mime);
http::response<http::file_body> 
build_file_response(std::string path);
http::response<http::empty_body>
build_response_empty_body(std::string path);
http::response<http::string_body>
build_not_found_response(std::string text,  beast::string_view mime);
http::response<http::string_body>
build_response_bad_request(std::string text,  beast::string_view mime);
http::response<http::string_body> 
build_response_internal_server_error(std::string text,  beast::string_view mime);
beast::string_view
mime_type(beast::string_view path);


const unsigned HTTP_VERSION = 11;


/**
 *  build_string_response
 */
http::response<http::string_body> build_string_response(std::string text,  beast::string_view mime)
{
      http::response<http::string_body> res{http::status::ok, HTTP_VERSION};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime);
        res.body() = text;
        res.prepare_payload();

    return res;
}


/**
 *  build_file_response
 */
http::response<http::file_body> 
build_file_response(std::string path)
{

    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    auto const size = body.size();

    http::response<http::file_body> res{
        std::piecewise_construct,
        std::make_tuple(std::move(body)),
        std::make_tuple(http::status::ok, HTTP_VERSION)};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path) );
    res.content_length(size);

    return res;
}


/**
 * build_response_empty_body
 */
http::response<http::empty_body>
build_response_empty_body(std::string path)
{
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    auto const size = body.size();

    http::response<http::empty_body> 
    res{http::status::ok, HTTP_VERSION};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    return res;
}


/**
 * build_response_not_found
 */
http::response<http::string_body>
build_not_found_response(std::string text,  beast::string_view mime)
{
    http::response<http::string_body> res{http::status::not_found, HTTP_VERSION};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime);
    res.body() =text;;
    res.prepare_payload();
    return res;
}


/**
 * build_response_bad_request
 */
http::response<http::string_body>
build_response_bad_request(std::string text,  beast::string_view mime)
{
    http::response<http::string_body> res{http::status::bad_request, HTTP_VERSION};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime);
    res.body() = text;
    res.prepare_payload();
    return res;
}


/**
 *  build_response_internal_server_error
 */
http::response<http::string_body> 
build_response_internal_server_error(std::string text,  beast::string_view mime)
{
    http::response<http::string_body> res{http::status::internal_server_error, HTTP_VERSION};
    res.set(http::field::server,BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime);
    res.body() = text;
    res.prepare_payload();
    return res;
}


/**
 * mime_type
 * Return a reasonable mime type based on the extension of a file.
 */
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if(pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if(iequals(ext, ".htm"))  return "text/html";
    if(iequals(ext, ".html")) return "text/html";
    if(iequals(ext, ".php"))  return "text/html";
    if(iequals(ext, ".css"))  return "text/css";
    if(iequals(ext, ".txt"))  return "text/plain";
    if(iequals(ext, ".js"))   return "application/javascript";
    if(iequals(ext, ".json")) return "application/json";
    if(iequals(ext, ".xml"))  return "application/xml";
    if(iequals(ext, ".swf"))  return "application/x-shockwave-flash";
    if(iequals(ext, ".flv"))  return "video/x-flv";
    if(iequals(ext, ".png"))  return "image/png";
    if(iequals(ext, ".jpe"))  return "image/jpeg";
    if(iequals(ext, ".jpeg")) return "image/jpeg";
    if(iequals(ext, ".jpg"))  return "image/jpeg";
    if(iequals(ext, ".gif"))  return "image/gif";
    if(iequals(ext, ".bmp"))  return "image/bmp";
    if(iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
    if(iequals(ext, ".tiff")) return "image/tiff";
    if(iequals(ext, ".tif"))  return "image/tiff";
    if(iequals(ext, ".svg"))  return "image/svg+xml";
    if(iequals(ext, ".svgz")) return "image/svg+xml";
    return "application/text";
}


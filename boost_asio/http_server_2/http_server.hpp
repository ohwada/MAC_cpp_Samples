/**
 *  http_server.hpp
 * 2022-06-01 K.OHWADA
 */

// HTTP Server with callback
// refrence: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_96s/main.cpp


#include <iostream>
#include <string>
#include <functional>
#include "boost/asio.hpp"
#include "file_util.hpp"


using Callback = std::function<void(std::string mag)>;


// prototype
void run_server(short const port, Callback callback);
bool save_server_request(std::string data);
bool read_index_html(std::string &text);
std::string build_response(std::string html);


/**
 *  class Session
 */
class Session : public std::enable_shared_from_this<Session>
{
public:
   Session(boost::asio::ip::tcp::socket socket) : 
      tcp_socket(std::move(socket))
   {
        setup();
   }

/**
 *  start
 */
   void start(Callback callback)
   {
        m_callback = callback;
        read();
   }

private:
/**
 *  setup
 */
   void setup()
   {
        std::string html;
        read_index_html(html);
        http_response = build_response(html);
}

/**
 *  read
 */
   void read()
   {
      auto self(shared_from_this());

      tcp_socket.async_read_some(
         boost::asio::buffer(data, data.size()),
         [this, self](std::error_code const ec, std::size_t const length)
      {
         if (!ec)
         {
            auto request = std::string(data.data(), length);
            // std::cout << request << std::endl;
            write(http_response);
            save_server_request(request);
            m_callback(request);
         }
      });
   }


/**
 *  write
 */
   void write(std::string_view response)
   {
      auto self(shared_from_this());

      tcp_socket.async_write_some(
         boost::asio::buffer(response.data(), response.length()),
         [this, self](std::error_code const ec, std::size_t const)
      {
         if (!ec)
         {
            read();
         }
      });
   }

    std::array<char, 1024>  data;
    boost::asio::ip::tcp::socket   tcp_socket;
    std::string http_response;
    Callback m_callback;
};
// class Session


/**
 *  class Server
 */
class Server
{
public:
   Server(boost::asio::io_context& context, short const port, Callback callback)
      : tcp_acceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
      , tcp_socket(context)
   {
        m_callback = callback;

        std::cout << "listen port: " << port << std::endl;

        accept();
   }


private:

/**
 *  accept
 */
   void accept()
   {
      tcp_acceptor.async_accept(tcp_socket, [this](std::error_code ec)
      {
         if (!ec)
         {
            std::make_shared<Session>(std::move(tcp_socket))->start( m_callback );
         }

         accept();
      });
   }

    boost::asio::ip::tcp::acceptor tcp_acceptor;
    boost::asio::ip::tcp::socket   tcp_socket;
    Callback m_callback;
};
// class Server


/**
 *  run_server
 */
void run_server(short const port, Callback callback)
{
   try
   {
      boost::asio::io_context context;

      Server srv(context, port, callback);

      context.run();
   }
   catch (std::exception const & e)
   {
      std::cerr << "exception: " << e.what() << std::endl;
   }
}


/**
 * save_server_request
 */
bool save_server_request(std::string data)
{
    std::string dir("log");
    std::string prefix("server_request");
    std::string ext("txt"); 
    std::string fname;

    getTimestampFileName(prefix, ext, fname);
    std::string path= make_path(dir, fname);

    return writeTextFile(path,  data );
}


/**
 * read_index_html
 */
bool read_index_html(std::string &text)
{
    std::string file("data/index.html");
    return readTextFile(file, text);
}


/**
 *  build_response
 */
std::string build_response(std::string html)
{

    const std::string CRLF("\r\n");

 const std::string HEADER_OK("HTTP/1.1 200 OK\r\n");
    const std::string HEADER_CONTENT_HTML("Content-Type: text/html\r\n");

    const std::string HEADER_CONTENT_LENGTH("Content-Length: ");

    const std::string CLOSE("Connection: Close\r\n");

    std::string content_length = 
    HEADER_CONTENT_LENGTH 
    +std::to_string( html.size() )
    + CRLF;

    std::string response = 
    HEADER_OK
    + HEADER_CONTENT_HTML
    +  content_length
    + CRLF
    + html;

    return response;
}




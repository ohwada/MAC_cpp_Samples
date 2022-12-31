/**
 * ws_ws_chat_client.hpp
 * 2022-10-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/ws_chat_client.cpp


#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include  "ws_request_builder.hpp"
#include  "ws_frame_common.hpp"
#include  "ws_client.hpp"


// prototype
bool ws_chat_client(std::string server, std::string port, std::string path);
std::vector<char>  do_handle_read_response(char* m_data, size_t bytes_transferred);
std::vector<char> do_handle_read_frame(char* data,  size_t bytes_transferred);


typedef std::deque<std::string> message_queue;


/**
 * class ws_chat_client
 */
class ws_chat_client
{
public:
/**
 * ws_chat_client
 */
  ws_chat_client(boost::asio::io_context& io_context,
      const boost::asio::ip::tcp::resolver::results_type& endpoints, std::string host, std::string path)
    : m_io_context(io_context),
     m_socket(io_context)
{
    m_handshake_finished = false;

    auto sec_key = gen_ws_sec_key(10);
    auto str_request = build_ws_request(host, path, sec_key);
    
    std::cout << std::endl;
    std::cout << "request" << std::endl;
    std::cout << str_request << std::endl;

    std::ostream request_stream(&m_request);
    request_stream << str_request;

    boost::asio::async_connect(m_socket, endpoints,
        boost::bind(&ws_chat_client::handle_connect, this,
          boost::asio::placeholders::error));
  }


/**
 * write
 */
  void write(const std::string& msg)
  {
        std::cout << "write: " << msg << std::endl;

        auto write_data = build_client_text(msg);
        auto write_data_size = write_data.size();

        if ( write_data_size > 0 ){
            dump_write_vec(write_data);
            boost::asio::async_write(m_socket,
            boost::asio::buffer( (char *)write_data.data(), write_data_size),
            boost::bind(&ws_chat_client::handle_write_frame, this,
            boost::asio::placeholders::error));
        }
  }


/**
 * close
 */
  void close()
  {
std::cout << "close" << std::endl;
    // boost::asio::post(m_io_context,
        // boost::bind(&ws_chat_client::do_close, this));
  }

private:
/**
 * handle_connect
 */
  void handle_connect(const boost::system::error_code& error)
  {
std::cout << "handle_connect" << std::endl;
    if (!error)
    {
        boost::asio::async_write(m_socket,  m_request,
          boost::bind(&ws_chat_client::handle_write_request, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Error: " << error.message() << "\n";
    }
}


/**
 *  handle_write_request
 */
  void handle_write_request(const boost::system::error_code& err)
  {
std::cout << "handle_write_request" << std::endl;
    if (!err)
    {
   m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
        boost::bind(&ws_chat_client::handle_read_response, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      std::cout << "Error: " << err.message() << "\n";
    }
  }


/**
 *  handle_read_response
 */
  void handle_read_response(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    std::cout << "handle_read_response" << std::endl;
    if (!error)
    {
do_handle_read_response(m_data, bytes_transferred);
m_handshake_finished = true;
// wait input message
std::cout << "enter message" << std::endl;

// wait next message
           m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
            boost::bind(&ws_chat_client::handle_read_frame, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle_read_frame
 */
  void handle_read_frame(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
        auto write_data = do_handle_read_frame(m_data,  bytes_transferred);
        auto write_data_size = write_data.size();

        if(write_data_size > 0) {
            dump_write_vec(write_data);
            boost::asio::async_write(m_socket,
            boost::asio::buffer( (char *)write_data.data(), write_data_size),
            boost::bind(&ws_chat_client::handle_write_frame, this,
            boost::asio::placeholders::error));
        } else {
// recurcive call myself
           m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
            boost::bind(&ws_chat_client::handle_read_frame, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle_write_frame
 */
  void handle_write_frame(const boost::system::error_code& error)
  {
    if (!error)
    {
     m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
          boost::bind(&ws_chat_client::handle_read_frame, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }


/**
 * do_write
 */
  void do_write(std::string msg)
  {
    std::cout << "do_write: " << msg << std::endl;

    if(!m_handshake_finished){
        std::cout << "not  handshake_finished" << std::endl;
        return;
    }

    bool write_in_progress = !m_write_msgs.empty();
    m_write_msgs.push_back(msg);

    if (!write_in_progress)
    {
        std::string text( m_write_msgs.front() );
        auto write_data = build_client_text(text);
        auto write_data_size = write_data.size();
        std::cout << "send text: " << text << std::endl;
        dump_write_vec(write_data);

        boost::asio::async_write(m_socket,
          boost::asio::buffer( (char *)write_data.data(),
            write_data_size ),
          boost::bind(&ws_chat_client::handle_write_frame, this,
            boost::asio::placeholders::error));
    }
  }


/**
 * do_close
 */
  void do_close()
  {
std::cout << "do_close" << std::endl;
   m_socket.close();
  }

private:
// warning: private field 'm_io_context' is not used
  boost::asio::io_context& m_io_context;

  boost::asio::ip::tcp::socket m_socket;

  enum { max_length = 1024 };
  char m_data[max_length];
  message_queue m_write_msgs;
  boost::asio::streambuf m_request;
    bool m_handshake_finished;
};



/**
 *  ws_chat_client
 */
bool ws_chat_client(std::string host, std::string port, std::string path)
{
  try
  {

    boost::asio::io_context io_context;

    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, port);

    class ws_chat_client c(io_context, endpoints, host, path);

    boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));

  enum { msg_length = 512 };

    char line[ msg_length];

    while ( std::cin.getline(line,  msg_length) )
    {
        std::string msg(line,  std::strlen(line));
        c.write(msg);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return false;
  }

  return true;
}

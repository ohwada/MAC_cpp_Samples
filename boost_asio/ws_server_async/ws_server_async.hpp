#pragma once
/**
 *  ws_server_async.hpp
 * 2022-10-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/async_tcp_echo_server.cpp
//
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include "ws_server.hpp"

// prototype
bool run_server(unsigned short port, int mode);
bool do_handle_read(char* data,  size_t bytes_transferred, bool is_handshake, int mode,   std::vector<char> &write_data);
std::vector<char> do_handle_write_response();

/**
 *  class session
 */
class session
{
public:
/**
 *  constractor
 */
  session(boost::asio::io_context& io_context)
    : socket_(io_context)
  {
        m_mode = MODE_ECHO;
        m_handshake = true;
  }


/**
 *  socket
 */
  boost::asio::ip::tcp::socket& socket()
  {
    return socket_;
  }


/**
 *  start
 */
  void start(int mode)
  {
    std::cout << "session start mode: " << mode << std::endl;
    m_mode = mode;
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
/**
 *  handle read
 */
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
// When Echo mode
// wait to next massage
// after recieve handshake response
// When NORMAL mode
// send first text
// when recieve handshake response

    if (!error)
    {
        std::vector<char> write_data;
        int res = do_handle_read(data_,  bytes_transferred, m_handshake, m_mode,  write_data);
        auto write_data_size = write_data.size();
        // std::cout << "res: " << res << std::endl;
        // std::cout << "write_data_size: " << write_data_size << std::endl;

        if(res == RES_HANDSHAKE) {
            m_handshake= false;
            if(write_data_size>0) {
                boost::asio::async_write(socket_,
                boost::asio::buffer( (char *)write_data.data(), write_data_size),
                boost::bind(&session::handle_write_response, this,
                boost::asio::placeholders::error));
            }
        } else {
            if(write_data_size>0) {
                dump_write_vec(write_data);
                boost::asio::async_write(socket_,
                boost::asio::buffer( (char *)write_data.data(), write_data_size),
                boost::bind(&session::handle_write, this,
                boost::asio::placeholders::error));
            } else {
// recurcive call myself
                socket_.async_read_some(boost::asio::buffer(data_, max_length),
                boost::bind(&session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
            }
        } // res
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle write
 */
  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle write response
 */
  void handle_write_response(const boost::system::error_code& error)
  {
// In Test mode
// send first text
// In other mode
// wait next message

    if (!error)
    {
        if(m_mode == MODE_TEST){
// send first text
                auto write_data = do_handle_write_response();
                auto write_data_size = write_data.size();
                if(write_data_size>0) {
                    dump_write_vec(write_data);
                    boost::asio::async_write(socket_,
                    boost::asio::buffer( (char *)write_data.data(), write_data_size),
                    boost::bind(&session::handle_write, this,
                    boost::asio::placeholders::error));
                }
        } else {
// wait next message
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        }
    }
    else
    {
      delete this;
    }
  }

boost::asio::ip::tcp::socket socket_;
enum { max_length = 1024 };
char data_[max_length];
int m_mode;
bool m_handshake;
};


/**
 *  class ws_server
 */
class ws_server
{
public:
/**
 *  constractor
 */
  ws_server(boost::asio::io_context& io_context, short port, int mode)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{  
    m_mode = mode;
    start_accept();
    std::cout << "listen: " << port << std::endl;
  }

private:
/**
 *  start_accept
 */
  void start_accept()
  {
    session* new_session = new session(io_context_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&ws_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }


/**
 *  handle accept
 */
  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start(m_mode);
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

boost::asio::io_context& io_context_;
 boost::asio::ip::tcp::acceptor acceptor_;
int m_mode;
};

 
/**
 *  run_server
 */
bool run_server(unsigned short port, int mode)
{
  try
  {

    boost::asio::io_context io_context;

    ws_server s(io_context, port, mode);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return false;
  }

  return true;
}

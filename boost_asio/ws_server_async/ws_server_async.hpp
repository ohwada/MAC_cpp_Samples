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
int do_handle_read_handshake(char* data,  size_t bytes_transferred,  std::string &write_data);
std::vector<char> do_handle_read_frame(char* data,  size_t bytes_transferred, int mode );
std::vector<char> do_handle_write_handshake();

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
        boost::bind(&session::handle_read_handshake, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
/**
 *  handle read_handshake
 */
  void handle_read_handshake(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    std::cout << " handle_read_handshake" << std::endl;
    if (!error)
    {
        std::string write_data;
        int res = do_handle_read_handshake(data_,  bytes_transferred, write_data);
    
        if(res == RES_HANDSHAKE) {
                boost::asio::async_write(socket_,
                boost::asio::buffer(write_data),
                boost::bind(&session::handle_write_handshake, this,
                boost::asio::placeholders::error));
        } else if(res == RES_BRAWSER) {
                boost::asio::async_write(socket_,
                boost::asio::buffer(write_data),
                boost::bind(&session::handle_write_brawser, this,
                boost::asio::placeholders::error));
        } // res
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle write handshake
 */
  void handle_write_handshake(const boost::system::error_code& error)
  {
// In Test mode
// send first text
// In other mode
// wait next message
    std::cout << " handle_write_handshake" << std::endl;
    if (!error)
    {
        if(m_mode == MODE_TEST){
// send first text
                auto write_data = do_handle_write_handshake();
                auto write_data_size = write_data.size();
                if(write_data_size>0) {
                    dump_write_vec(write_data);
                    boost::asio::async_write(socket_,
                    boost::asio::buffer( (char *)write_data.data(), write_data_size),
                    boost::bind(&session::handle_write_frame, this,
                    boost::asio::placeholders::error));
                }
        } else {
// wait next message
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&session::handle_read_frame, this,
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
 *  handle write brawser
 */
  void handle_write_brawser(const boost::system::error_code& error)
  {
    std::cout << " handle_write_brawser" << std::endl;
    if (!error)
    {
     // wait handshake
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&session::handle_read_handshake, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }


/**
 *  handle read_frame
 */
  void handle_read_frame(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    std::cout << " handle_read_frame" << std::endl;
    if (!error)
    {
        auto write_data =
        do_handle_read_frame(data_,  bytes_transferred, m_mode);
        auto write_data_size = write_data.size();
        if(write_data_size>0) {
                dump_write_vec(write_data);
                boost::asio::async_write(socket_,
                boost::asio::buffer( (char *)write_data.data(), write_data_size),
                boost::bind(&session::handle_write_frame, this,
                boost::asio::placeholders::error));
        } else {
// recurcive call myself
                socket_.async_read_some(boost::asio::buffer(data_, max_length),
                boost::bind(&session::handle_read_frame, this,
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
 *  handle write_frame
 */
  void handle_write_frame(const boost::system::error_code& error)
  {
    std::cout << " handle_write_frame" << std::endl;
    if (!error)
    {
// wait next message
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read_frame, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
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

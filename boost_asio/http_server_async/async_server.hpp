/**
 *  http_server_async.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/boostorg/asio/blob/develop/example/cpp03/echo/async_tcp_echo_server.cpp
//
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

// prototype
bool run_server(unsigned short port, std::string doc_root);
  std::string do_handle_read(std::string doc_root, std::string read_data);


/**
 *  class session
 */
class session
{
public:
  session(boost::asio::io_context& io_context)
    : socket_(io_context)
  {
  }

  boost::asio::ip::tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

void set_doc_root(std::string doc_root)
{
        m_doc_root = doc_root;
}

private:
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
        std::string read_data(data_,  bytes_transferred);
        std::string write_data = do_handle_read(m_doc_root, read_data);

      boost::asio::async_write(socket_,
          boost::asio::buffer(write_data),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error));

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

 boost::asio::ip::tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
    std::string m_doc_root;
};


/**
 *  class server
 */
class server
{
public:
  server(boost::asio::io_context& io_context, short port, std::string doc_root)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
  {  
    m_doc_root = doc_root;
    start_accept();
    std::cout << "listen: " << port << std::endl;
  }

private:
  void start_accept()
  {
    session* new_session = new session(io_context_);
    new_session->set_doc_root(m_doc_root);

    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
    std::string m_doc_root;
};

 
/**
 *  run_server
 */
bool run_server(unsigned short port, std::string doc_root)
{
  try
  {

    boost::asio::io_context io_context;

    server s(io_context, port, doc_root);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return false;
  }

  return true;
}

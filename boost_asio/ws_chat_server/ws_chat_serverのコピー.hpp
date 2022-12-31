/**
 * ws_chat_server.hpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/chat_server.cpp

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include "chat_message.hpp"
#include "ws_server.hpp"


// prototype
bool run_server(unsigned short port);
int do_handle_read_handshake(char* data,  size_t bytes_transferred,  std::string &write_data);
int do_handle_read_frame(char* data,  size_t bytes_transferred, std::vector<char> &write_data);
std::vector<char> server_text( std::string text);


typedef std::deque<std::string> message_queue;


/**
 * class chat_participant
 */
class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const std::string& msg) = 0;

};


typedef boost::shared_ptr<chat_participant> chat_participant_ptr;


/**
 * class chat_room
 */
class chat_room
{
public:
/**
 * join
 */
  void join(chat_participant_ptr participant)
  {
std::cout << "chat_room: join" << std::endl;
    participants_.insert(participant);
    std::for_each(m_recent_msgs.begin(), m_recent_msgs.end(),
        boost::bind(&chat_participant::deliver,
          participant, boost::placeholders::_1));
  }


/**
 * leave
 */
  void leave(chat_participant_ptr participant)
  {
std::cout << "chat_room; leave" << std::endl;
    participants_.erase(participant);
  }


/**
 * deliver
 */
  void deliver(const std::string& msg)
  {
std::cout << std::endl;
std::cout << "chat room deliver: " << msg << std::endl;
    m_recent_msgs.push_back(msg);

    while (m_recent_msgs.size() > max_recent_msgs){
      m_recent_msgs.pop_front();
} // while

    std::for_each(participants_.begin(), participants_.end(),
        boost::bind(&chat_participant::deliver,
          boost::placeholders::_1, boost::ref(msg)));
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  message_queue m_recent_msgs;

};


/**
 * class chat_session
 */
class chat_session
  : public chat_participant,
    public boost::enable_shared_from_this<chat_session>
{
public:
/**
 *  chat_session
 */
  chat_session(boost::asio::io_context& io_context, chat_room& room)
    : socket_(io_context),
      room_(room)
  {
        m_id = 0;
        m_handshake_finished = false;
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
  void start(int id)
  {
    std::cout << "chat session start: " << id << std::endl;
    m_id = id;
    room_.join(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(m_data, max_length),
        boost::bind(&chat_session::handle_read_handshake, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }


/**
 *  deliver
 */
  void deliver(const std::string& msg)
  {
        std::cout << std::endl;
        debug_text("deliver", msg);

       if(!m_handshake_finished) {
                debug_info("handshake not finished");
                return;
        }

        bool write_in_progress = !m_write_msgs.empty();
        m_write_msgs.push_back(msg);
    if (!write_in_progress)
    {
        auto data = server_text( m_write_msgs.front() );
        auto size = data.size();
        if(size > 0 ){
            debug_write_vec("deliver", data);
            boost::asio::async_write(socket_,
            boost::asio::buffer( data.data(), size ),
            boost::bind(&chat_session::handle_write_msgs, shared_from_this(),
            boost::asio::placeholders::error));
        }
    }
  }


/**
 * handle_write_msgs
 */
  void handle_write_msgs(const boost::system::error_code& error)
  {
        debug_info("handle_write_msgs");
    if (!error)
    {
      m_write_msgs.pop_front();
      if (!m_write_msgs.empty())
      {
        auto data = server_text( m_write_msgs.front() );
        auto size = data.size();
        if(size > 0){
            debug_write_vec("handle_write_msgs", data);
// recurcive call
            boost::asio::async_write(socket_,
            boost::asio::buffer( data.data(), size ),
            boost::bind(&chat_session::handle_write_msgs, shared_from_this(),
              boost::asio::placeholders::error));
        }
      }
    }
    else
    {
      room_.leave(shared_from_this());
    }
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
        int res = do_handle_read_handshake(m_data,  bytes_transferred, write_data);

        if(res == RES_HANDSHAKE) {
                boost::asio::async_write(socket_,
                boost::asio::buffer(write_data),
                boost::bind(&chat_session::handle_write_handshake, this,
                boost::asio::placeholders::error));
        } else if(res == RES_BRAWSER) {
                boost::asio::async_write(socket_,
                boost::asio::buffer(write_data),
                boost::bind(&chat_session::handle_write_brawser, this,
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
    std::cout << " handle_write_handshake" << std::endl;
    if (!error)
    {
        m_handshake_finished = true;
// wait next message
        socket_.async_read_some(boost::asio::buffer(m_data, max_length),
        boost::bind(&chat_session::handle_read_frame, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
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
            socket_.async_read_some(boost::asio::buffer(m_data, max_length),
            boost::bind(&chat_session::handle_read_handshake, this,
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
        debug_info("handle_read_frame");
    if (!error)
    {
        std::vector<char> write_data;
        int res = do_handle_read_frame(m_data,  bytes_transferred, write_data);
        auto write_data_size = write_data.size();

        if(res == RES_TEXT) {
            std::string msg(write_data.begin(), write_data.end() );
            room_.deliver( msg);
            write_data_size = 0;
        }

            if(write_data_size>0) {
                    dump_write_vec(write_data);
                boost::asio::async_write(socket_,
                boost::asio::buffer( (char *)write_data.data(), write_data_size),
                boost::bind(&chat_session::handle_write_frame, this,
                boost::asio::placeholders::error));
            } else {
// recurcive call myself
                socket_.async_read_some(boost::asio::buffer(m_data, max_length),
                boost::bind(&chat_session::handle_read_frame, this,
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
        debug_info("handle_write_frame");
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(m_data, max_length),
          boost::bind(&chat_session::handle_read_frame, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }


/**
 *  debug_info
 */
void debug_info(std::string info)
{
    std::string FORMAT("chat session %d) %s");
    std::cout << ( boost::format(FORMAT) % m_id % info ) << std::endl;
}


/**
 *  debug_text
 */
void debug_text(std::string name, std::string text)
{
    std::string FORMAT("chat session %d) %s: %s");
    std::cout << ( boost::format(FORMAT) % m_id % name % text ) << std::endl;
}

/**
 *  debug_write_vec
 */
void debug_write_vec(std::string name, std::vector<char> data)
{
    std::string FORMAT("chat session %d) %s");
    std::cout << ( boost::format(FORMAT) % m_id % name ) << std::endl;
    dump_write_vec(data);
}


  boost::asio::ip::tcp::socket socket_;
  chat_room& room_;

  message_queue m_write_msgs;
enum { max_length = 1024 };
char m_data[max_length];
bool m_handshake_finished;
int m_id;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;


/**
 * class chat_server
 */
class chat_server
{
public:
  chat_server(boost::asio::io_context& io_context,
      const boost::asio::ip::tcp::endpoint& endpoint)
    : io_context_(io_context),
      acceptor_(io_context, endpoint)
  {
        m_cnt = 0;
        start_accept();
  }

  void start_accept()
  {
    chat_session_ptr new_session(new chat_session(io_context_, room_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&chat_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(chat_session_ptr session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
        m_cnt ++;
        session->start(m_cnt);
    }

    start_accept();
  }

private:
  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  chat_room room_;
 int m_cnt;
};



/**
 * run_server
 */
bool run_server(unsigned short port)
{

  try
  {
        boost::asio::io_context io_context;

            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);

        std::cout << "listen: " << port << std::endl;

        chat_server s(io_context, endpoint);

        io_context.run();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return false;
  }

  return true;
}


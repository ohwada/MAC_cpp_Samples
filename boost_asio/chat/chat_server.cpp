/**
 * chat_server.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/boostorg/asio/blob/develop/example/cpp03/chat/chat_server.cpp

#include <iostream>
#include "chat_server.hpp"
#include "port.h"

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

using namespace std; // For atoi.


/**
 * main
 */
int main(int argc, char* argv[])
{
    const size_t BUFSIZE = 10;
    unsigned short ports[BUFSIZE];
    ports[0] = PORT;
    int port_count = 1;

    if (argc >= 2) {
          port_count = 0;
        for (int i = 1; i < argc; i++){
            int j = i-1;
            if(j<BUFSIZE) {
                ports[j] = atoi(argv[i]);
                port_count ++;
            }
        } // for
    } else {
        cout << "Usage: chat_server <port> [<port> ...] " << endl;
    }

  try
  {

    chat_server_list servers;
    boost::asio::io_context io_context;

        for (int i = 0; i < port_count; i++){
            int port =  ports[i];
            std::cout << "port: " << port << std::endl;
            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
            chat_server_ptr server(new chat_server(io_context, endpoint));
            servers.push_back(server);
        } // for

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

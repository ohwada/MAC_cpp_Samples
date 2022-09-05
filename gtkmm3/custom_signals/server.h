// File: server.h (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/chapter-custom-signals-example.html'

#ifndef GTKMM_EXAMPLE_SERVER_H
#define GTKMM_EXAMPLE_SERVER_H

#include <sigc++/sigc++.h>

class Server
{
public:
  Server();
  virtual ~Server();

  void do_something();

  //signal accessor:
  typedef sigc::signal<void, bool, int> type_signal_something;
  type_signal_something signal_something();

protected:
  type_signal_something m_signal_something;
};

#endif //GTKMM_EXAMPLE_SERVER_H

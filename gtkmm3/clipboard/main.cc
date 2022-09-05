// File: main.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-clipboard-examples.html

#include "examplewindow.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  ExampleWindow window;
  //Shows the window and returns when it is closed.
  Gtk::Main::run(window);

  return 0;
}
// File: main.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-pushbuttons.html#pushbutton-example

#include "buttons.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Buttons buttons;
  //Shows the window and returns when it is closed.
  Gtk::Main::run(buttons);

  return 0;
}

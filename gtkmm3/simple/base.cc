// File: base.cc (For use with gtkmm 3, not gtkmm 2)
///  https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-basics-simple-example.html

#include <gtkmm.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Gtk::Window window;

  Gtk::Main::run(window);

  return EXIT_SUCCESS;
}

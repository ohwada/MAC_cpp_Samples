/**
 * window.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://shopping2.gmobb.jp/htdmnr/www08/cpp/gtkmm01.html

#include <gtkmm.h>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Gtk::Window window;
    Gtk::Main::run(window);
  return 0;
}

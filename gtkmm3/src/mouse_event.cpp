/**
 * mouse_event.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://shopping2.gmobb.jp/htdmnr/www08/cpp/gtkmm01.html


#include <gtkmm.h>
#include <iostream>


/**
 * class MainWin
 */
class MainWin : public Gtk::Window 
{
  public:
    MainWin() {
        add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
        signal_button_press_event().connect(sigc::mem_fun(*this, &MainWin::on_click));
        signal_button_release_event().connect(sigc::mem_fun(*this, &MainWin::on_release));
    }

  private:
    bool on_click(GdkEventButton* event) {
// mouse click
        std::cout << "click\n";
        return true;
    }

    bool on_release(GdkEventButton* event) { 
// mouse release
        std::cout << "release\n";
        return true;
    }
};


/**
 * main
 */
int main(int argc, char *argv[]) 
{
    Gtk::Main kit(argc, argv);
    MainWin mainwin;
    Gtk::Main::run(mainwin);

    return 0;
}


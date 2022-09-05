/**
 * box_button.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://shopping2.gmobb.jp/htdmnr/www08/cpp/gtkmm01.html

#include <gtkmm.h>


/**
 * class MainWin
 */
class MainWin : public Gtk::Window 
{
   // Gtk::Button btUp = Gtk::Button("＋");
    // Gtk::Button btDn = Gtk::Button("-");

    int zoom = 14;
 Gtk::Button btUp, btDn;
    Gtk::Label lbZoom;
    Gtk::HBox hbox;

public:
    MainWin();

private:
    void btUpClicked();
    void btDnClicked();
};


/**
 * constractor
 */
MainWin::MainWin()
{
    btUp.set_label("＋");
    btDn.set_label("－");

    lbZoom.set_text(std::to_string(zoom));
    hbox.pack_start(btUp);
    hbox.pack_start(lbZoom);
    hbox.pack_start(btDn);

//  connect signals and slots
    btUp.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btUpClicked));
    btDn.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btDnClicked));

    add(hbox);
    show_all_children();
}


/**
 * btUpClicked
* / slot function
 */
void MainWin::btUpClicked() 
{
    if (zoom >= 14) return;
    zoom++;
    lbZoom.set_text(std::to_string(zoom));
}    


/**
 * btDnClicked
* / slot function
 */
void MainWin::btDnClicked() 
{
    if (zoom <= 8) return;
    zoom--;
    lbZoom.set_text(std::to_string(zoom));
}    


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



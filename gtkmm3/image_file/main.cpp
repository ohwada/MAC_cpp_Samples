/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#include <iostream>
#include <string>
#include "ImageWindow.h"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
	string file("images/uparrow.png");

    if(argc == 2) {
    		file = argv[1];
	} else {
        cout << "Usage: " <<  argv[0] << " <imageFile> " << endl;
    }

cout << file << endl;

	auto app = Gtk::Application::create(argc, argv);

	ImageWindow window(file);

	return app->run(window);
}

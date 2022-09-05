/**
 * ImageWindow.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#include <iostream>
#include <glibmm/fileutils.h>
#include "ImageWindow.h"


/**
 * constrctor
 */
ImageWindow::ImageWindow(std::string file)
{

	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
try{
	pixbuf = Gdk::Pixbuf::create_from_file(file);
} catch( Glib::FileError e) {
        std::cerr << "exception: " << e.what() << std::endl;
		return;
} catch( Gdk::PixbufError e) {
        std::cerr << "exception: " << e.what() << std::endl;
		return;
}

 int width = pixbuf->get_width(); 
 int height = pixbuf->get_height(); 

std::cout << "width: " << width << std::endl;
std::cout << "height: " << height << std::endl;

	set_title ("gtkmm");
	set_default_size(width, height);

	image.set(pixbuf);

	add(image);

	show_all();
}


/**
 * destrctor
 */
ImageWindow::~ImageWindow()
{
	// none
}

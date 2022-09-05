#pragma once
/**
 * ImageWindow.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#ifndef IMAGE_WINDOW_H_
#define IMAGE_WINDOW_H_

#include <string>
#include <gtkmm/window.h>
#include <gtkmm/image.h>


/**
 * ImageWindow
 */
class ImageWindow : public Gtk::Window
{
public:
	ImageWindow(std::string file);
	virtual ~ImageWindow();

protected:
	Gtk::Image image;
};

#endif /* IMAGE_WINDOW_H_ */

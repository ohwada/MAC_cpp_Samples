// https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#ifndef SAMPLEWINDOW_H_
#define SAMPLEWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/image.h>

class SampleWindow : public Gtk::Window
{
public:
	SampleWindow();
	virtual ~SampleWindow();

protected:
	Gtk::Image image;

};

#endif /* SAMPLEWINDOW_H_ */

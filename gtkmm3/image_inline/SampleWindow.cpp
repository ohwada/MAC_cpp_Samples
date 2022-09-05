// https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#include "SampleWindow.h"

//gdk-pixbuf-csource --raw --name=sample_png sample.png > sample.png.h
#include "img/sample.png.h"

SampleWindow::SampleWindow()
{
	set_default_size(320, 240);

	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_inline(-1, sample_png);
	image.set(pixbuf);

	add(image);
	show_all();
}

SampleWindow::~SampleWindow()
{
}

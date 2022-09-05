// https://blogs.osdn.jp/2018/03/20/gtkmm-animation-gif.html#google_vignette

#include <gtkmm/application.h>

#include "SampleWindow.h"

int main(int argc, char* argv[])
{
	auto app = Gtk::Application::create(argc, argv);

	SampleWindow window;
	return app->run(window);
}

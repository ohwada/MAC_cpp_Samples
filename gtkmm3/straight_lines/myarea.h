//File: myarea.h (For use with gtkmm 3, not gtkmm 2)
  //http://transit.iut2.upmf-grenoble.fr/doc/gtkmm-3.0/tutorial/html/sec-cairo-drawing-lines.html

#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif // GTKMM_EXAMPLE_MYAREA_H

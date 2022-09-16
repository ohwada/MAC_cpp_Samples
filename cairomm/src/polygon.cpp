/**
 *  polygon.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/Perukii/items/5caf86ca5274e9f98e80

#include <iostream>
#include <cairomm/context.h>

using namespace std;


/**
 *  main
 */
int main()
{
// Create an ImageSurface
    Cairo::RefPtr<Cairo::ImageSurface> surface = 
        Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, 300, 300);

// Create a Context that captures the drawing content  
    Cairo::RefPtr<Cairo::Context> cr = 
        Cairo::Context::create(surface);

// specify the color to use : lightpink
    cr->set_source_rgba(1.0,0.8,0.8,1.0);
    cr->paint();

// pink
    cr->set_source_rgba(1.0,0.7,0.7,1.0);

// Specify the polygon to be drawn as a path 
// specify the starting point with move_to
    cr->move_to(70,70);
    cr->line_to(250,50);
    cr->line_to(230,230);
    cr->line_to(50,250);

// close the path
    cr->close_path();

// Draw the fill within the range 
// At this time, the drawing range is saved. 
// You can also fill with cr->fill(), but the drawing range is not saved, so you cannot add borders, etc.
    cr->fill_preserve();

// red
    cr->set_source_rgba(1.0,0.0,0.0,1.0);

    // specify border thickness
    cr->set_line_width(1.0);

// draw border
    cr->stroke();

// Output ImageSurface to PNG
    string file("cairo.png");
    surface->write_to_png(file);

    cout<<  "created " << file << endl;

    return 0;
}

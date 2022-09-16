/**
 *  bgcolor.cpp
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
    cr->set_source_rgba(1.0, 0.8, 0.8, 1.0);

// paint
    cr->paint();

// Output ImageSurface to PNG
    string file("cairo.png");
    surface->write_to_png(file);

    cout<<  "created " << file << endl;

    return 0;
}
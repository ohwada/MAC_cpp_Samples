gtkmm3: straight_lines
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gtkmm3/screenshots/lines.png" width="300" /> 

### overview
The Cairo Drawing Model  
The basic concept of drawing in Cairo involves defining 'invisible' paths and then stroking or filling them to make them visible.
To do any drawing in gtkmm with Cairo, You must first create a Cairo::Context object.   
This class holds all of the graphics state parameters that describe how drawing is to be done.   
This includes information such as line width, color, the surface to draw to, and many other things.   
This allows the actual drawing functions to take fewer arguments to simplify the interface. In gtkmm, a Cairo::Context is created by calling the Gdk::Window::create_cairo_context() function.   
Since Cairo contexts are reference-counted objects, this function returns a Cairo::RefPtr<Cairo::Context> object.

Drawing Straight Lines  
We'll start with the simplest of drawing elements: the straight line.   
But first you need to know a little bit about Cairo's coordinate system.   
The origin of the Cairo coordinate system is located in the upper-left corner of the window with positive x values to the right and positive y values going down.

In this example, we'll construct a small but fully functional gtkmm program and draw some lines into the window.   
The lines are drawn by creating a path and then stroking it.   
A path is created using the functions Cairo::Context::move_to() and Cairo::Context::line_to().   
The function move_to() is similar to the act of lifting Your pen off of the paper and placing it somewhere else -- no line is drawn between the point you were at and the point You moved to. To draw a line between two points, use the line_to() function.

### samplrs
- myarea.cc

Build and Run:
% make lines
% bin/lines

gtkmm3: printing
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gtkmm3/screenshots/printing.png" width="300" /> 

### overview
Printing  
gtkmm's printing API provides dialogs that are consistent across applications and allows us of Cairo's common drawing API, with Pango-driven text rendering.   
In the implementation of this common API, platform-specific backends and printer-specific drivers are used.

This  example demonstrates how to print some input from a user interface.   
It shows how to implement on_begin_print and on_draw_page, as well as how to track print status and update the print settings.



### samplrs
- printformoperation.cc

Build and Run:
% make print
% bin/print

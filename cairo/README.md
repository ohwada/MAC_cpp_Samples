cairo
===============

cairo sample <br/>

draw arc to png file <br/>

Cairo is a 2D graphics library with support for multiple output devices <br/>
https://www.cairographics.org/ <br/>

###  install cairo
% brew install cairo <br/>
https://formulae.brew.sh/formula/cairo <br/>

### arc.c <br/>
draw arc to png file <br/>

build sample code <br/>
% gcc arc.c -o arc `pkg-config --cflags --libs cairo` <br/>

run sample code  <br/>
%  ./arc <br/>

display as below <br/>
cairo version: 1.16.0  <br/>
saved: cairo.png   <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cairo/result/arc.png" width="300" /><br/>

## ibm_cairo_logo.c <br/>
draw IBM logo in GTK window <br/>

build sample code <br/>
reqire gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK <br/>

% gcc ibm_cairo_logo.c -o ibm `pkg-config --cflags --libs cairo` `pkg-config --cflags --libs gtk+-2.0`  <br/>

### run sample code 
%  ./ibm <br/>

draw IBM logo in GTK window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/cairo/result/screenshot_ibm_logo.png" width="300" /><br/>


### Reference <br/>
- https://www.boost.org/


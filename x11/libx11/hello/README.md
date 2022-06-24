X11 hello
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/libx11/hello/hello.png" width="300" /> <br/>

X11 Sample <br/>
draw hello on X11 window

Build and Run <br/>
(1) cmake <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>
% ./hello <br/>

(2) gcc with pkgconfig <br/>
% gcc hello.c -o hello `pkg-config --cflags --libs x11` <br/>
% ./hello <br/>
 

### Reference
- https://uguisu.skr.jp/Windows/x11.html


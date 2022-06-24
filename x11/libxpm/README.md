X11 libxpm
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/x11/libxpm/scrrenshots/sxpm_gray_xpm.png" width="300" /> <br/>

X11 Sample <br/>

 libxpm :  <br/>
X Pixmap (XPM) image file format library  <br/>
https://www.x.org/wiki/  <br/>

### install
% brew install libxpm  <br/>
https://formulae.brew.sh/formula/libxpm  <br/>
% pkg-config --cflags --libs xpm  <br/>

#### sxpm.c  <br/>
draw xpm image on X11 Window <br/> <br/>

Require : <br/>
- libxpm  <br/>
- libxt  <br/>
- libext  <br/>

Build and Run <br/>
% cd build <br/>
% cmake .. <br/>
% make <br/>
% ./sxpm -version <br/>


### Reference
- https://cgit.freedesktop.org/xorg/lib/libXpm/




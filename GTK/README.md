GTK
===============

GTK Sample <br/>
open GTK window <br/>
and show image <br/>

 
### install gtk
% brew install gtk+ <br/>

## gtk_hello_world.cpp
open GTK window <br/>

### build sample code 
% g++ gtk_hello_world.cpp -o hello -std=c++11 `pkg-config --cflags --libs gtk+-2.0` <br/>

### run sample code 
% ./hello  <br/>

### result 
display as below <br/>
GTK: Hello World <br/>
GTK Version: 2.24.32 <br/>

open GTK window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/GTK/result/screenshot_hello.png" width="300" /><br/>


## test_image_file.cpp
open GTK window <br/>
load image from image file <br/>
show image <br/>

### build sample code 
% g++ test_image_file.cpp  parse_filename.cpp -o image -std=c++11 `pkg-config --cflags --libs gtk+-2.0` <br/>


### run sample code 
Usage:  image \< inputImageFilename /\>  <br/>
ex)
% ./image ./images/uparrow.png <br/>


### result 
display as below <br/>
GTK: imagebfile <br/>
load image: ./images/uparrow.png <br/>
Number of channels:	4 <br/>
Has Alpha channel:	1 <br/>
Bits per sample:	8 <br/>
Width:	512 <br/>
Height:	512 <br/>
Bytes of row:	2048 <br/>


open GTK window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/GTK/result/screenshot_uparrow.png" width="300" /><br/>


## test_pixel.cpp
open GTK window <br/>
show pixel image <br/>

### build sample code 
g++ test_pixel.cpp  pixels.c -o pixel -std=c++11 `pkg-config --cflags --libs gtk+-2.0` <br/>

### run sample code 
USAGE: ./pixel [size] [sscale]  <br/>
ex)
% pixel 2 128 <br/>

### result 
display as below <br/>
GTK: ColorMatrix <br/>
ColorMatrix: 256 x 256 <br/>

open GTK window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/GTK/result/screenshot_pixel_2_128.png" width="300" /><br/>


### Reference <br/>
- https://www.gtk.org/
-  https://developer.gnome.org/gtk-tutorial/stable/c39.html#SEC-HELLOWORLD
 - https://fut-nis.hatenadiary.jp/entry/20121113/1352810731


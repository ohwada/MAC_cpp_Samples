sfml
===============

sfml sample <br/>
open sfml window and show image from file <br/>

Simple and Fast Multimedia Library <br/>
https://www.sfml-dev.org/ <br />

## install sfml
% brew install sfml <br/>
https://formulae.brew.sh/formula/sfml <br/>

## draw_circle.cpp
draw green circle <br/>

build code  <br/>
% g++ src/draw_circle.cpp  -o circle `pkg-config --cflags --libs sfml-graphics` <br/>

run code  <br/>
% ./circle <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/sfml/result/screenshot_circle.png" width="300" /><br/>


## helloworld.cpp
// draw text "Hello, World !" with font file <br/>

### build code 
% g++ src/helloworld.cpp  -std=c++11 -o hello `pkg-config --cflags --libs sfml-graphics` <br/>

### run code 
% ./hello <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/sfml/result/screenshot_hello.png" width="300" /><br/>

## draw_pixels.cpp
draw pixcels from memory <br/>

build code  <br/>
% g++ src/draw_pixels.cpp src/pixels.c  -o pixcels `pkg-config --cflags --libs sfml-graphics` <br/>

run code  <br/>
Usage: ./pixcels [size] [scale] <br/>
ex) <br/>
% ./pixcels 4 32 <br/>

draw pixcels <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/sfml/result/screenshot_pixels.png" width="300" /><br/>


## show_image.cpp
show image from fie <br/>

build code  <br/>
% g++ src/show_image.cpp src/parse_filename.cpp  -o show `pkg-config --cflags --libs sfml-graphics` <br/> 


run code  <br/> 
Usage: ./show \< imageFile \> <br/>
ex) <br/>
% ./show ./images/uparrow.png <br/>

display as below <br/>
loaded: images/uparrow.png ( 512 x 512 ) <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/sfml/result/screenshot_uparrow.png" width="300" /><br/>


### Reference <br/>
-  https://riptutorial.com/sfml
- https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php



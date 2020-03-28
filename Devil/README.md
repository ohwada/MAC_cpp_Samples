Devi
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/Devil/images/devil_logo.jpg" width="300" /><br/>

Devil Sample <br/>
read and write Image File <br/>

### Caution
Devil saving images upside-down
- https://www.gamedev.net/forums/topic/467011-devil-saving-images-upside-down/


### install Devi
% brew install devil <br/>


## test_read_write_image_file.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
%  g++ test_read_write_image_file.cpp parse_filename.cpp -o test -std=c++11 `pkg-config --cflags --libs il` <br/>

### run sample code 
Usage: test \< inputImageFilename \>  <br/>
ex)
% ./test ./images/uparrow.png <br/>

### result 
display as below <br/>
Devil : read write image file <br/>
Devil Version: 180 <br/>
load Image: ./images/uparrow.png <br/>
Width: 512  Height: 512  Depth: 1  Bpp: 32 <br/>
saved Image: uparrow_copy.png <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++  test_gtk.cpp devil_util.cpp  parse_filename.cpp -o gtk   `pkg-config --cflags --libs il` `pkg-config --cflags --libs gtk+-2.0`


### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.png <br/>

### result 
display as below <br/>
Devil : gtk  <br/>
loadImage: ./images/uparrow.png ( 512 x 512 ) <br/>

read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/Devil/result/screenshot_gtk_uparrow.png" width="300" /><br/>


## test_gl.cpp
read image file <br/>
show image in OpenGL window <br/>

### build sample code
requires <br/>
- macOS OpenGL framework <br/>
- macOS GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

 % g++  test_gl.cpp devil_util.cpp parse_filename.cpp -o gl  -framework OpenGL  -framework GLUT  `pkg-config --cflags --libs il` <br/>



### run sample code 
Usage: gl \< inputImageFilename \>  <br/>
ex)
% ./gl ./images/uparrow.png <br/>

### result 
display as below <br/>
Devil: OpenGL <br/>
loadImage: ./images/uparrow.png ( 512 x 512 ) <br/>

read image file <br/>
show image in OpenGL window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/Devil/result/screenshot_gl_uparrow.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++  test_write.cpp devil_util.cpp pixels.c -o write `pkg-config --cflags --libs il` 



### run sample code 
Usage: write [size] [scale] [outputFileExtension]
ex)
 ./write 2 256 png


### result 
display as below <br/>
Devil : write <br/>
saved Image: test_2_256.png <br/>

write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/Devil/result/test_2_256.png" width="300" /><br/>


### Reference <br/>
- http://openil.sourceforge.net/  
- https://github.com/DentonW/DevIL/tree/master/DevIL/examples/simple_example


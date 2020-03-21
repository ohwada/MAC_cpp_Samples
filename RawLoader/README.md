RawLoader
===============

RawLoader Sample <br/>
read Raw format image file <br/>

### about Raw Image Format  
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/RawLoader/images <br/>

## test_gl.cpp 
load Texture from  Raw format image file <br/>
show in OpenGL window  <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

display following warning when build <br/>
but don't mind <br/>
warning: 'glutInit' is deprecated: first deprecated in macOS 10.9

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

% g++ test_gl.cpp RawLoader.cpp parse_raw_filename.cpp parse_filename.cpp -o gl -std=c++11 -framework OpenGL -framework GLUT 

### run sample code
Usage: gl <inputImageFile> <br/> 
ex)   <br/>
% ./gl ./images/uparrow_512_512_1.data <br/>

quit when enter 'q' <br/>

### result 
display as below <br/>
RawLoader test  <br/>
loadImage: ./images/uparrow_512_512_1.raw ( 512 x 512 ) <br/>


open OpenGL window <br/>
read Raw format image file  <br/>
draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/RawLoader/result/screenshot_gl_uparraow.png" width="300" /><br/>


## test_gtk.cpp 
load image from  Raw format image file <br/>
show in GTK window  <br/>

### build asample code 
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

% g++ test_gtk.cpp RawLoader.cpp  parse_raw_filename.cpp parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`

### run sample code
Usage: gtk <inputImageFile> <br/> 
ex)   <br/>
% ./gtk  ./images/uparrow_512_512_1.data <br/>

### result 
display as below <br/>


read Raw format image file  <br/>
show in GTK window <br/>
 <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/RawLoader/result/screenshot_gtk_uparrow.png" width="300" /><br/>


### Reference <br/>
- http://asura.iaigiri.com/OpenGL/gl4.html


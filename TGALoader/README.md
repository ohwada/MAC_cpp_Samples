TGALoader
===============

TGALoader Sample <br/>
read TGA format image file <br/>

this sample support fullcolor  uncompressed tga format <br/>
support origin left bottom and left top <br/>


## test_gl.cpp 
read TGA format image file <br/>
show in OpenGL window <br/>

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

### build asample code 
% g++  test_gl.cpp  TGALoader.cpp parse_filename.cpp  -o gl -std=c++11  -framework OpenGL  -framework GLUT

### run sample code
Usage: gl <inputImageFile> <br/> 
ex)   <br/>
% ./gl ./images/uparrow.tga <br/>

quit when enter 'q' <br/>

### result 
display as below <br/>
TGALoader: gl <br/>
read : ./images/uparrow.tga <br/>
TGA size: 512 x 512 <br/>


open OpenGL window <br/>
and read TGA file  <br/>
and draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/TGALoader/result/screenshot_gl_uparrow.png" width="300" /><br/>


### test_gtk.cpp 
read TGA format image file <br/>
show in GTK window <br/>

### build asample code 
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

% g++ test_gtk.cpp TGALoader.cpp  parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`

### run sample code
Usage: gtk <inputImageFile> <br/> 
ex)   <br/>
% ./gtk ./images/uparrow.tga <br/>

### result 
display as below <br/>
TGALoader : gtk <br/>
read : ./images/uparrow.tga <br/>
TGA size: 512 x 512 <br/>


open GTK window <br/>
read TGA file  <br/>
show in GTK window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/TGALoader/result/screenshot_gtk_uparrow.png" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- http://www.openspc2.org/format/TGA/index.html
- http://asura.iaigiri.com/OpenGL/gl5.html


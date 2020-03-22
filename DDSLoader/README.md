DDSLoader
===============

DDSLoader Sample <br/>
read DDS format image file <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>


% g++  test_loader.cpp  DDSLoader.cpp parse_filename.cpp  -o test -std=c++11  -framework OpenGL  -framework GLUT

### run sample code
Usage: test <inputImageFile> <br/> 
ex)   <br/>
% ./test  ./images/uparrow.dds <br/>

quit when enter 'q' <br/>

### result 
display as below <br/>
dds: OpenGL
loadImage: ./images/uparrow.dds ( 512 x 512 ) <br/>
DDS format: DXT5 <br/>


open OpenGL window <br/>
and read DDS file  <br/>
and draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/DDSLoader/result/screenshot_uparrow.png" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- http://www.openspc2.org/format/TGA/index.html
- http://asura.iaigiri.com/OpenGL/gl5.html


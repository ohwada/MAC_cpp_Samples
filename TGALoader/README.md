OpenGL-TGALoader
===============

OpenGL/GLUT Sample <br/>
load Texture from TGA format image file <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

% g++  test_TGALoader.cpp  TGALoader.cpp parse_filename.cpp  -o test -std=c++11  -framework OpenGL  -framework GLUT

display following warning when build <br/>
but don't mind <br/>
warning: 'glutInit' is deprecated: first deprecated in macOS 10.9

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

### run sample code
Usage: test \< inputImageFile \> <br/> 
ex)   <br/>
% ./test ./images/sample.tga <br/>

quit when enter 'q' <br/>

### result 
display as below <br/>
OpenGL test TGALoader <br/>
OpenGL Vender: Intel Inc. <br/>
read : ./images/sample.tga <br/>


open OpenGL window <br/>
and read TGA file  <br/>
and draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-TGALoader/result/screenshot_sample.png" width="300" /><br/>

NOTE : <br/>
it will be upside down,  <br/>
when mapping the image on the Texture <br/>

### Reference <br/>
- https://www.opengl.org/
- http://www.openspc2.org/format/TGA/index.html
- http://asura.iaigiri.com/OpenGL/gl5.html


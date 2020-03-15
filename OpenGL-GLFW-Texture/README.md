OpenGL-GLFW-Texture
===============

OpenGL/glfw Sample <br/>
dwaw Texture with image <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>
- glfw <br/>
https://www.glfw.org/ <br/>
% brew install glfw <br/>
- Devil <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/Devil


% g++ test_texture.cpp texture_util.cpp devil_util.cpp parse_filename.cpp -o test -std=c++11  -framework OpenGL `pkg-config --cflags --libs glfw3`  `pkg-config --cflags --libs il` <br/>



display following warning when build <br/>
but don't mind <br/>
warning: 'glCreateShader' is deprecated: first
      deprecated in macOS 10.14 - OpenGL API deprecated  <br/>

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

### run sample code
Usage: test \< inputImageFile \> <br/>
ex)
% ./test ./images/uparrow.png <br/>

### result 
display as below <br/>
OpenGL/glfw Texture <br/>
 readImage: ./images/uparrow.png ( 512 x 512 )  <br/>
OpenGL Vender: Intel Inc. <br/>


read image file <br/>
open OpenGL window <br/>
draw  Texture with image <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLFW-Texture/result/screenshot_uparrow.png" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- https://www.glfw.org/
- http://freeimage.sourceforge.net/
- http://nn-hokuson.hatenablog.com/entry/2017/02/24/171230


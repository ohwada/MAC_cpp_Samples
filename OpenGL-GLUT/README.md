OpenGL-GLUT
===============

OpenGL/GLUT Sample <br/>


### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

display following warning when build <br/>
but don't mind <br/>
warning: 'glClear' is deprecated: first deprecated in macOS 10.14

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

## hello_window.cpp
open OpenGL window <br/>

### build asample code 
% g++  hello_window.cpp  -o hello_window -std=c++11  -framework OpenGL  -framework GLUT

### run sample code 
% ./hello_window <br/>

### result 
display as below <br/>
OpenGL/GLUT hello window <br/>
OpenGL Vender: Intel Inc. <br/>
OpenGL Renderer: Intel(R) HD Graphics 6000 <br/>
OpenGL Version: 2.1 INTEL-14.4.23 <br/>
GLUT Version: 5 <br/>

open OpenGL window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_hello_window.png" width="300" /><br/>

## triangle.cpp
draw triangle <br/>

### build asample code 
% g++ triangle.cpp  -o triangle -std=c++11  -framework OpenGL  -framework GLUT

### run sample code 
% ./triangle <br/>

### result 
draw triangle <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_triangle.png" width="300" /><br/>

## teapot.cpp
draw teapot <br/>

### build asample code 
% g++ teapot.cpp  -o teapot -std=c++11  -framework OpenGL  -framework GLUT

### run sample code
Usage teapot [mode]
ex) 
% ./teapot 2 <br/>

mode  <br/>
- 0 : wireframe <br/>
- 1 : solid white <br/>
- 2 : solid ads (Ambient, Diffuse, and Specular) <br/>

### result 
mode 0 : wireframe <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_wireteapot.png" width="300" /><br/>

mode 1 : solid white <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_solidteapot__white.png" width="300" /><br/>

mode 2 : solid ads <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_solidteapot_ads.png" width="300" /><br/>

### result 
draw teapot <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT/result/screenshot_teapot.png" width="300" /><br/>

### Reference <br/>
- https://www.opengl.org/
- https://www.opengl.org/resources/libraries/glut/
- http://math.hws.edu/graphicsbook/source/glut/first-triangle.c




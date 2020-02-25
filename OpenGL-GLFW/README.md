OpenGL-GLFW
===============

OpenGL/glfw Sample <br/>

open OpenGL window with glfw <br/>
and draw triangle <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

- glfw <br/>
https://www.glfw.org/ <br/>
% brew install glfw <br/>

display following warning when build <br/>
but don't mind <br/>
warning: 'glClear' is deprecated: first deprecated in macOS 10.14

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

## hello_window.cpp
open OpenGL window <br/>

### build asample code 
% g++ hello_window.cpp  -o hello_window -std=c++11  -framework OpenGL `pkg-config --cflags --libs glfw3` <br/>

### run sample code 
% ./hello_window <br/>

### result 
display as below <br/>
OpenGL/glfw3 Hello <br/>
OpenGL Vender: Intel Inc. <br/>
OpenGL Renderer: Intel(R) HD Graphics 6000 <br/>
OpenGL Version: 2.1 INTEL-14.4.23 <br/>
glfw Version: 3.3.2 Cocoa NSGL EGL OSMesa dynamic <br/>

open OpenGL window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLFW/result/screenshot_hello_window.png" width="300" /><br/>

## triangle.cpp
draw triangle <br/>

### build asample code 
% g++ triangle.cpp -o triangle -std=c++11  -framework OpenGL `pkg-config --cflags --libs glfw3` <br/>

### run sample code 
% ./triangle <br/>

### result 
display as below <br/>
OpenGL/glfw3 Triangle <br/> 
OpenGL Version: 4.1 INTEL-14.4.23 <br/> 

draw triangle <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLFW/result/screenshot_triangle.png" width="300" /><br/>

### Reference <br/>
- https://www.opengl.org/
- https://www.glfw.org/
- https://github.com/itoru257/GLFWDemo-Mac




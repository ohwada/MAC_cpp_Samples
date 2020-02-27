OpenGL-GLSL
===============

OpenGL/GLSL Sample <br/>

open OpenGL window with glfw and glad  <br/>
and draw Triangle with GLSL  (OpenGL Shading Language)  <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

- glfw <br/>
https://www.glfw.org/ <br/>
% brew install glfw <br/>

- glm <br/>
https://glm.g-truc.net/0.9.9/index.html <br/>
% brew install glm <br/>

- glad <br/>
https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library#glad_.28Multi-Language_GL.2FGLES.2FEGL.2FGLX.2FWGL_Loader-Generator.29 <br/>
% pip install glad <br/>

% g++ ./src/*.cpp ./glad/src/glad.c -o main -std=c++11  -framework OpenGL `pkg-config --cflags --libs glfw3` `pkg-config --cflags --libs glm` -I./glad/include  -I./src <br/>


display following warning when build <br/>
but don't mind <br/>
warning: treating 'c' input as 'c++' when in C++ mode <br/>

### run sample code 
Usage: main recipe-name <br/>
Recipe names:  <br/>
- basic :  <br/>
draw Triangle <br/>
- basic-attrib : <br/>
print active attributes. <br/>
- basic-debug :  <br/>
display debug messages. <br/>
but does not work on macOS <br/>
- basic-uniform :  <br/>
render rotating Triangle <br/>
- basic-uniform-block :  <br/>
draw Circle  <br/>

ex)
% ./main basic <br/>


### result 
display as below <br/>
OpenGL/GLFW/glad: basic <br/>
GL Vendor    : Intel Inc. <br/>
GL Renderer  : Intel(R) HD Graphics 6000 <br/>
GL Version   : 4.1 INTEL-14.4.23 <br/>
GL Version   : 4.1 <br/>
GLSL Version : 4.10 <br/>

open OpenGL window <br/>
and draw Triangle <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLSL/result/screenshot_basic.png" width="300" /><br/>

#### basic-uniform :  <br/>
draw rotating Triangle <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLSL/result/screenshot_basic_unuiform.png" width="300" /><br/>

#### basic-uniform-block :  <br/>
draw Circle <br/>
inner color is Yellow  <br/>
outer color is Red  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLSL/result/screenshot_basic_unuiform_block.pngg" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language
- https://www.glfw.org/
- https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library#glad_.28Multi-Language_GL.2FGLES.2FEGL.2FGLX.2FWGL_Loader-Generator.29
- https://github.com/daw42/glslcookbook/tree/master/chapter01


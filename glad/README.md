glad
===============

glad <br/>
Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator <br/>
https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library#glad_.28Multi-Language_GL.2FGLES.2FEGL.2FGLX.2FWGL_Loader-Generator.29 <br/>

### install glad 
% pip install glad <br/>

% glad --generator=c --extensions=GL_EXT_framebuffer_multisample,GL_EXT_texture_filter_anisotropic --out-path=GL

created GL directory as below <br/>
GL <br/>
    include <br/>
        KHR<br/>
            khrplatform.h <br/>
        glad <br/>
            glad.h <br/>
    src <br/>
        glad.c<br/>

### requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>

### simple.c
show OpenGL window <br/>

build sample code <br/>
% gcc example/simple.c GL/src/glad.c -o simple -framework OpenGL  -framework GLUT  -IGL/include <br/>

run sample code <br/>
% ./simple <br/>

display as below <br/>
OpenGL Version 2.1 <br/> 
OpenGL 2.1 INTEL-14.5.22 <br/>
GLSL 1.20 <br/>

show pink window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/glad/result/screenshot_simple.png" width="300" /><br/>

### hellowindow2.cpp
show OpenGL window with glfw <br/>

require glfw <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenGL-GLFW <br/>

build sample code <br/>
g++ example/hellowindow2.cpp  GL/src/glad.c -o hellow -framework OpenGL `pkg-config --cflags --libs glfw3` -I./GL/include <br/>

run sample code <br/>
% ./hellow <br/>

display as below <br/>
Starting GLFW context, OpenGL 3.3 <br/>
OpenGL 4.1 INTEL-14.5.22 <br/>

show cyan window <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/glad/result/screenshot_hellow.png" width="300" /><br/>

### sdl.cpp
show SDL window <br/>

require SDL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/SDL <br/>

build sample code <br/>
g++ example/sdl.cpp GL/src/glad.c -o sdl `pkg-config --cflags --libs sdl2` -IGL/include <br/>

run sample code <br/>
% ./sdl <br/>

display as below <br/>
OpenGL version loaded: 2.1<br/>

show green triangle in black background <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/glad/result/creenshot_sdl.png" width="300" /><br/>


### Reference 
- https://github.com/Dav1dde/glad
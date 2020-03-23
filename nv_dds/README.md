nv_dds
===============

dds Sample <br/>
read and write dds format Image File <br/>

nv-dds updates/ bugfixes for the DDS loader from the NVIDIA SDK <br/>

## test_copy.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
% g++ test_copy.cpp nv_dds.cpp parse_filename.cpp -DNV_DDS_NO_GL_SUPPORT=1 -o copy <br/>


### run sample code 
Usage: copy \< inputImageFilename \>  <br/>
ex)
% ./copy ./images/uparrow.dds <br/>

### result 
display as below <br/>
dds : copy  <br/>
loadImage: ./images/uparrow.dds ( 512 x 512 ) <br/>
saved image: uparrow_copy.dds <br/>


## test_gl.cpp
read image file <br/>
show image in OpenGL window <br/>

### build sample code
requires <br/>
- macOS OpenGL framework <br/>
- macOS GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

 % g++ test_gl.cpp nv_dds.cpp parse_filename.cpp  -o gl  -framework OpenGL  -framework GLUT <br/>

### run sample code 
Usage: gl \< inputImageFilename \>  <br/>
ex)
% ./gl ./images/woman.dds <br/>

### result 
display as below <br/>
dds: OpenGL <br/>
loadImage: ./images/woman.dds ( 512 x 512 ) <br/>


read image file <br/>
show image in OpenGL window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/nv_dds/result/screenshot_woman.png" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- https://github.com/paroj/nv_dds


FreeType
===============

FreeType Sample <br/>

###  install FreeType
% brew install freetype

###  get Font File
- https://github.com/liberationfonts/liberation-fonts/releases/tag/2.1.0

## test_freetype.cpp <br/>
read font file <br/>
write font glyph image to file <br/>

### build asample code 
% g++ test_freetype.cpp `pkg-config --cflags --libs freetype2`

### result 
display as below  <br/>
Render letter of given font as a TGA image.  <br/>
writeTGA: test_a.tga ( 90 x 92 )  <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeType/result/test_b.tga.png" /><br/>

## test_TextRenderer.cpp <br/>
read font file <br/>
show text in OpenGL window <br/>

### build asample code 
requires  <br/>
- macOS  OpenGL framework <br/>
- macOS  GLUT framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>

% g++  test_TextRenderer.cpp  TextRenderer.cpp -std=c++11  -framework OpenGL   -framework GLUT `pkg-config --cflags --libs freetype2`

display following warning when build <br/>
but don't mind <br/>
warning: 'glClear' is deprecated: first deprecated in macOS 10.14

Note: <br/>
https://pc.watch.impress.co.jp/docs/news/1125772.html

### result 
draw Blue text <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeType/result/screenshot_test_TextRenderer.png" width="300" /><br/>


### Reference <br/>
- https://www.freetype.org/
- https://www.opengl.org/
- https://github.com/benhj/glfreetype


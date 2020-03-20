OpenGL-GLUT-Texture
===============

OpenGL/GLUT Sample <br/>
dwaw Texture with image <br/>

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

## test_texture.cpp <br/>
  % g++ test_texture.cpp texture_util.cpp -o test -std=c++11 -framework OpenGL -framework GLUT 

### run sample code
Usage: test \< mode \> \< image size \> <br/>
- mode 1 <br/>
use Color Matrix pattern <br/>
- mode 2 <br/>
use CheckerBoard pattern <br/>
ex)   <br/>
% ./test 1 2 <br/>

Operation by key input <br/>
- 'q' <br/>
quit this program <br/>
- 't' <br/>
toggle to draw twice horizontally or not <br/>
- Space bar <br/>
toggle to spin or not <br/>

### result 
display as below <br/>
OpenGL/GLUT Texture <br/>
Usage: ./test \< mode \> \< image size \> <br/> 
OpenGL Vender: Intel Inc. <br/>

open OpenGL window <br/>
and draw  Texture with color array pattern <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT-Texture/result/screenshot_test_1_2.png" width="300" /><br/>

% ./test 2 16 <br/>
and draw  Texture with CheckerBoard pattern <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT-Texture/result/screenshot_test_2_16.png" width="300" /><br/>


## image_texture.cpp <br/>
  % g++ image_texture.cpp texture_util.cpp parse_filename.cpp -o image -std=c++11 -framework OpenGL -framework GLUT 

### run sample code
Usage: image \< inputImageFile \> <br/>
ex) <br/>
 % ./image ./images/park.tga

### result 
display as below <br/>
OpenGL/GLUT Texture <br/>
loadImage: ./images/park.tga ( 512 x 512 ) <br/>


open OpenGL window <br/>
and read TGA file <br/>
and draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT-Texture/result/screenshot_park.png" width="300" /><br/>


### Reference <br/>
- https://www.opengl.org/
- http://www.openspc2.org/format/TGA/index.html
- http://asura.iaigiri.com/OpenGL/gl5.html


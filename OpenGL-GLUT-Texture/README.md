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
  % g++ image_texture.cpp texture_util.cpp TGALoader.cpp parse_filename.cpp -o image -std=c++11 -framework OpenGL -framework GLUT 

### run sample code
Usage: image \< inputImageFile \> <br/>
ex) <br/>
 % ./image ./images/upsidedown.tga

### result 
display as below <br/>
OpenGL/GLUT Texture <br/>
Usage: ./image \< inputImageFile \> <br/> 
OpenGL Vender: Intel Inc. <br/>


open OpenGL window <br/>
and read TGA file <br/>
and draw  Texture <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenGL-GLUT-Texture/result/screenshot_upsidedown.png" width="300" /><br/>

NOTE : <br/>
it will be upside down,  <br/>
when mapping the image on the Texture <br/>


### Reference <br/>
- https://www.opengl.org/
- http://www.openspc2.org/format/TGA/index.html
- http://www.oit.ac.jp/is/L231/pukiwiki/index.php?%E6%84%9F%E8%A6%9A%E3%83%A1%E3%83%87%E3%82%A3%E3%82%A2%E7%A0%94%E7%A9%B6%E5%AE%A4/OpenGL/%E3%83%86%E3%82%AF%E3%82%B9%E3%83%81%E3%83%A3%E3%83%9E%E3%83%83%E3%83%94%E3%83%B3%E3%82%B0#s205ba9e

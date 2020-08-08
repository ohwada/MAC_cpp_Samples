stb_image
===============

sample code for stb_image.h <br/>
load image file <br/>
stb is single-file public domain libraries  for C/C++ <br/>
https://github.com/nothings/stb

## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>


- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

build sample code <br/>
 % g++ test_gtk.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0` -I./include

run sample code <br/> 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.png <br/>

display as below <br/>
stb : gtk  <br/>
channels = 4  <br/>
loadImage: ./images/uparrow.png ( 510 x 510 )  <br/>

show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb_image/result/screenshot_uparrow.png" width="300" /><br/>


## test_write.cpp
write test bitmap pattern to image file <br/>

build sample code <br/>
% g++ test_write.cpp pixels.c  -o write -std=c++11 -I./include

run sample code <br/> 
Usage: write [size] [scale] [extension]
ex)
 ./write 2 256 png


display as below <br/>
bmp : write <br/>
saved Image : test_2_256.png <br/>


write test bitmap pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb_image/result/test_2_256.png" width="300" /><br/>

## conv_gray.cpp
convert to gray scall  <br/>

build sample code <br/>
% g++ conv_gray.cpp -o gray -std=c++11 -I./include <br/>

run sample code <br/> 
Usage: ./gray \< inputImageFile \> <br/>
ex) <br/>
% ./gray images/lena.bmp <br/>

display as below <br/>
stb : gray<br/>
loaded: images/lena.bmp (512 x 512 )<br/>
saved : lena_gray.bmp <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb_image/result/lena_gray.bmp" width="300" /><br/>

### Reference <br/>
- https://github.com/nothings/stb



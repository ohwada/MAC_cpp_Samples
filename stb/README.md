stb
===============

stb_image Sample <br/>
read write Image File <br/>
stb is single-file public domain libraries <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.png <br/>

### result 
display as below <br/>
stb : gtk  <br/>
channels = 4  <br/>
loadImage: ./images/uparrow.png ( 510 x 510 )  <br/>


read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb/result/screenshot_uparrow.png" width="300" /><br/>

gray image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb/result/screenshot_gray.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp pixels.c  -o write -std=c++11


### run sample code 
Usage: write [size] [scale] [extension]
ex)
 ./write 2 256 png


### result 
display as below <br/>
bmp : write <br/>
saved Image : test_2_256.png <br/>


write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/stb/result/test_2_256.png" width="300" /><br/>


### Reference <br/>
- https://github.com/nothings/stb



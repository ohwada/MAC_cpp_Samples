libpng
===============

libpng Sample <br/>
read and write png format Image File <br/>

## install libpng
% brew install libpng <br/>

## install png++
% brew install png++ <br/>


## test_copy.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
% g++ test_copy.cpp parse_filename.cpp -o copy -std=c++11  `pkg-config --cflags --libs libpng` -I/usr/local/include/png++ <br/>

### run sample code 
Usage: copy \< inputImageFilename \>  <br/>
ex)
% ./copy ./images/uparrow.png <br/>

### result 
display as below <br/>
libpng : copy
libpng Version: 1.6.37 <br/>
loadImage: ./images/uparrow.png ( 512 x 512 ) <br/>
saved Image : uparrow_copy.png <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp parse_filename.cpp -o gtk -std=c++11 `pkg-config --cflags --libs libpng`  `pkg-config --cflags --libs gtk+-2.0` -I/usr/local/include/png++

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.png <br/>

### result 
display as below <br/>
libpng : gtk  <br/>
loadImage: ./images/uparrow.png ( 512 x 512 ) <br/>


read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libpng/result/screenshot_upsrrow.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp  pixels.c -o write -std=c++11 `pkg-config --cflags --libs libpng` -I/usr/local/include/png++


### run sample code 
Usage: write [size] [scale] 
ex)
 ./write 2 256


### result 
display as below <br/>
libpng : write <br/>
saved Image: test_2_256.png <br/>

write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libpng/result/test_2_256.png" width="300" /><br/>


### Reference <br/>
- http://www.libpng.org/pub/png/libpng.html
- https://www.nongnu.org/pngpp/


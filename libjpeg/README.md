libjpeg
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libjpeg/images/libjpeg_logo.jpg" /><br/>

libjpeg Sample <br/>
read and write jpeg format Image File <br/>

## install libjpeg
% brew install libjpeg <br/>


## test_copy.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
% g++ test_copy.cpp jpeg.cpp parse_filename.cpp -o copy -std=c++11 `pkg-config --cflags --libs libjpeg` <br/>

### run sample code 
Usage: copy \< inputImageFilename \>  <br/>
ex)
% ./copy ./images/uparrow.jpg <br/>

### result 
display as below <br/>
bjpeg : copy  <br/>
libjpeg version:  9.4 <br/>
saved Image: uparrow_copy.jpg <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp jpeg.cpp  parse_filename.cpp -o gtk -std=c++11 `pkg-config --cflags --libs libjpeg` `pkg-config --cflags --libs gtk+-2.0` <br/>

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.jpg <br/>

### result 
display as below <br/>
libjpeg : gtk  <br/>
loadImage: ./images/uparrow.jpg ( 512 x 512 ) <br/>


read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libjpeg/result/screenshot_uparrow.jpg" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp jpeg.cpp  pixels.c parse_filename.cpp -o write -std=c++11 `pkg-config --cflags --libs libjpeg` <br/>


### run sample code 
Usage: write [size] [scale] 
ex)
 ./write 2 256


### result 
display as below <br/>
libjpeg : write <br/>
saved Image : test_2_256.jpg <br/>

write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libjpeg/result/test_2_256.jpg" width="300" /><br/>


### Reference <br/>
- http://libjpeg.sourceforge.net/
- https://github.com/md81544/libjpeg_cpp


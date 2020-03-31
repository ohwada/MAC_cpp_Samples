libtiff
===============

libtiff Sample <br/>
read and write tiff format Image File <br/>

## install libtiff
% brew install libtiff <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs libtiff-4`  `pkg-config --cflags --libs gtk+-2.0`

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.tiff <br/>

### result 
display as below <br/>
libtiff : gtk  <br/>
loadImage: ./images/uparrow.tiff ( 512 x 512 ) <br/>

read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libtiff/result/screenshot_uparrow.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp pixels.c  -o write -std=c++11  `pkg-config --cflags --libs libtiff-4`


### run sample code 
Usage: write [size] [scale] 
ex)
 ./write 2 256


### result 
display as below <br/>
bmp : write <br/>
saved Image : test_2_256.tif <br/>


write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libtiff/result/test_2_256.tif.png" width="300" /><br/>


### Reference <br/>
- http://www.simplesystems.org/libtiff/
- http://maptools-org.996276.n3.nabble.com/reading-rgb-values-from-16-bits-tif-images-td3390.html
- http://mf-atelier.sakura.ne.jp/mf-atelier/modules/tips/libs/libtiff/libtiff_write_8bit.html


FreeImage
===============

FreeImage Sample <br/>
read and write Image File <br/>


###　Caution
FreeImage macOS Version has <br/>
the BUG that swwaps between Red ch and Blue ch <br/>
and reverse upside down <br/>

- https://sourceforge.net/p/freeimage/discussion/36110/thread/28c0cdfd/


### install FreeImage
% brew install freeimage <br/>


## test_read_write_image_file.cpp
read image file <br/>
write image file as copy <br/>
convert image to gray <br/>
write gray image to file <br/>

### build sample code 
%  g++ test_read_write_image_file.cpp freeimage_util.cpp parse_filename.cpp -o test -std=c++11  -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage <br/>

### run sample code 
Usage: test \< inputImageFilename \>  <br/>
ex)
% ./test ./images/uparrow.png <br/>

### result 
display as below <br/>
FreeImage : read write <br/>
FreeImage : 3.18.0 <br/>
loadImage: ./images/uparrow.png ( 512 x 512 ) <br/>


read image file <br/>  
and save gray image to output file  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeImage/result/vegetables_gray.jpg" width="300" /><br/>

## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>

 % g++ test_gtk.cpp freeimage_util.cpp parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`  -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/uparrow.png <br/>

### result 
display as below <br/>
FreeImage with GTK:  <br/>
loadImage: ./images/uparrow.png  <br/>

read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeImage/result/screenshot_uparrow.png" width="300" /><br/>

## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp freeimage_util.cpp pixels.c  -o write -std=c++11  -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage

### run sample code 
Usage: write [size] [scale] [outputFileExtension]
ex)
 ./write 2 256 png


### result 
display as below <br/>
FreeImage : write <br/>
saved Image: test_2_256.png <br/>

write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeImage/result/test_2_256.png" width="300" /><br/>


### Reference <br/>
- http://freeimage.sourceforge.net/  <br/>
- http://downloads.sourceforge.net/freeimage/FreeImage3180.pdf  <br/>



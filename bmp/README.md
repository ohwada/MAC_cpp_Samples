bmp
===============

bmp Sample <br/>
read and write bmp format Image File <br/>

this sample support 24 bit uncompressed bmp format <br/>

## test_copy.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
% g++ test_copy.cpp bitmap.c  parse_filename.cpp -o copy  -std=c++11 <br/>

### run sample code 
Usage: copy \< inputImageFilename \>  <br/>
ex)
% ./copy ./images/uparrow.png <br/>

### result 
display as below <br/>
bmp : copy <br/>
loadImage: ./images/uparrow.bmp ( 512 x 512 ) <br/>
saved Image : uparrow_copy.bmp <br/>


## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp bitmap.c  parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/door.bmp <br/>

### result 
display as below <br/>
bmp : gtk  <br/>
loadImage: ./images/door.bmp ( 480 x 640 )  <br/>


read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/screenshot_door.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp bitmap.c  pixels.c  -o write -std=c++11


### run sample code 
Usage: write [size] [scale] 
ex)
 ./write 2 256


### result 
display as below <br/>
bmp : write <br/>
saved Image : test_2_256.bmp <br/>


write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/test_2_256.bmp" width="300" /><br/>


##　Exercises for Image Processing

#### exercise_gray.cpp
convert to grayscale <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/door_gray.bmp" width="300" /><br/>

#### exercise_post.cpp
posterization <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/door_post.bmp" width="300" /><br/>

#### exercise_sobel.cpp
edge detection by Sobel algorithm <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/lena_sobel.bmp" width="300" /><br/>

#### exercise_sobel_binary.cpp
edge detection by Sobel algorithm <br/>
binarization <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/lena_sobel_bin.bmp" width="300" /><br/>

#### exercise_thermo.cpp
generate thermography <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/door_thermo.bmp" width="300" /><br/>

### online ervice <br/>
convert to 24 bit bmp <br/>
https://www.petitmonte.com/labo/imageconvert/ <br/>

### Reference <br/>
- https://github.com/kawasin73/todai-bmp


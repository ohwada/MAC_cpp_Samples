OpenCV-ImageReadWrite
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/images/opencv_logo.png" width="150" /><br/>

OpenCV Sample <br/>
read and write Image File <br/>

### install OpenCV
% brew install opencv <br/>

##  test_read_write_image_file.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
require: OpenCV <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCV-ImageReadWrite <br/>

% g++  test_read_write_image_file.cpp parse_filename.cpp -o test -std=c++11 `pkg-config --cflags --libs opencv4` <br/>

### run sample code 
% ./test ./images/uparrow.png <br/>

### result 
read image file  <br/>  
write copy to output file  <br/>
convert grayscale  <br/>
write gray to output file  <br/>
 ex ) vegetables_gray.jpg  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/vegetables_gray.jpg" width="300" /><br/>

and show image  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/screenshot_imshow_vegitables.png" width="300" /><br/>

## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp parse_filename.cpp -o gtk -std=c++11 `pkg-config --cflags --libs opencv4`  `pkg-config --cflags --libs gtk+-2.0`

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/baboon.tiff <br/>

### result 
display as below <br/>
OpenCV with GTK:  <br/>
loadImage: ./images/baboon.tiff ( 512 x 512 ) <br/>

read image file <br/>
show image in GTK window <br/> 
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/screenshot_gtk_baboon.png" width="300" /><br/>

## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp pixels.c  -o write -std=c++11 `pkg-config --cflags --libs opencv4`

### run sample code 
Usage: ./write [size] [scale] [outputFileExtension] <br/>
ex) <br/>
./write 2 256 png <br/>

### result 
display as below <br/>
penCV : write <br/>
saved Image: test_2_256.png <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/test_2_256.png" width="300" /><br/>

### Reference <br/>
- https://opencv.org/  <br/>


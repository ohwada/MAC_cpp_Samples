OpenCV-ImageReadWrite
===============

OpenCV Sample <br/>
read and write Image File <br/>

### install OpenCV
% brew install opencv <br/>

### build sample code 
% g++  image_read_write.cpp parse_filename.cpp -o image_read_write -std=c++11 `pkg-config --cflags --libs opencv4` <br/>

### run sample code 
% ./image_read_write ./images/vegetables.jpg <br/>

### result 
read image file  <br/>  
ex ) vegetables.jpg <br/>
and show image  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/screenshot_imshow.png" width="300" /><br/>

and write output file  <br/>
 ex ) vegetables_gray.jpg  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-ImageReadWrite/result/vegetables_gray.jpg" width="300" /><br/>

### Reference <br/>
- https://opencv.org/  <br/>


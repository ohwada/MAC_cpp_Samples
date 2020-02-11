OpenCV-GaussianBlur
===============

OpenCV Sample <br/>
process Image with OpenCV GaussianBlur API <br/>
Gaussian Blur is  smoothing an image <br/>

### build sample code 
require: OpenCV <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCV-ImageReadWrite <br/>


% g++ GaussianBlur.cpp parse_filename.cpp  -o GaussianBlur -std=c++11 `pkg-config --cflags --libs opencv4` <br/>

### run sample code 
Usage:  GaussianBlur  <inputImageFile> <radius> <sigma> <br/>
ex ) <br/>
% ./GaussianBlur  ./images/opencv_logo.png 5 3.0 <br/>

### result 
read image file <br/>  
ex ) opencv_logo.png <br/>
and convert Image with GaussianBlur <br/>
and write to output file  <br/>
ex ) opencv_logo_11x11_3.0_.png <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-GaussianBlur/result/opencv_logo_11x11_3.0_.png" width="300" /><br/>

### Reference 
- https://opencv.org/  <br/>

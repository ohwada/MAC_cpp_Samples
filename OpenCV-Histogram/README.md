OpenCV-Hisotgram
===============

OpenCV Sample <br/>
Histogram <br/>

// calculate Histogram with OpenCV calcHist API <br/>

## histogram_gray.cpp 
load image as grayscale  <br/>
and create brightness Histogram <br/>

### build sample code 
require: OpenCV <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCV-ImageReadWrite <br/>

% g++  histogram_gray.cpp  histogram_util.cpp parse_filename.cpp -o histogram_gray -std=c++11 `pkg-config --cflags --libs opencv4`

### run sample code 
% ./histogram_gray <br/>

### result
display as below <br/>
OpenCV Version: 4.2.0 <br/>
save to: baboon_gray_hist.txt <br/>
save to: baboon_gray_hist.png <br/>

read image file <br/>  
calculate histogram <br/> 
save to text file <br/> 
save to image file <br/> 

show histogram in graph  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-Histgram/result/screenshot_gray.png" width="300" /><br/>


## histogram_color.cpp 
load image as color  <br/>
and create RGB Histogram <br/>

### build sample code 
require: OpenCV <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCV-ImageReadWrite <br/>

% g++  histogram_color.cpp  histogram_util.cpp parse_filename.cpp -o histogram_color -std=c++11 `pkg-config --cflags --libs opencv4`

### run sample code 
Usage: histogram_color \< inputImageFile \> [numBins] <br/>
ex)   <br/>
% ./histogram_color  ./images/baboon.jpg  <br/>

### result
display as below <br/>
OpenCV Version: 4.2.0 <br/>
save to: baboon_256_hist.txt <br/>
save to: baboon_256_hist.png <br/>

read image file <br/>  
calculate histogram <br/> 
save to text file <br/> 
save to image file <br/> 

show histogram in graph  <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV-Histgram/result/screenshot_color.png" width="300" /><br/>


### Reference 
- https://opencv.org/  <br/>
- https://github.com/opencv/opencv/blob/master/samples/cpp/demhist.cpp


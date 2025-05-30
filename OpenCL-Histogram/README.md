OpenCL-Histogram
===============

OpenCL Sample <br/>
ImageHistogram <br/>

// calculate Histogram in RGB values in the pixels of the Image
In the pixels of the image <br/>
// sum to 257 Red bins, followed by 257 Green bins and then the 257 Blue bins <br/>


## test_histogram.cpp <br/>
use test data with random values <br/>
check the value calculated by GPU with the value calculated by CPU <br/>

### build sample code 
requires  <br/>
- macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>

% g++ test_histogram.cpp  histogram_util.cpp  -o test_histogram -std=c++11 -framework OpenCL <br/>

display following warning  <br/>
but don't mind <br/>
warning: 'clCreateImage2D' is deprecated:  <br/>

### run sample code 
% ./test_histogram <br/>


display as below <br/>
Device Vendor: Intel Inc.  <br/>
Image Histogram for image type = CL_RGBA, CL_UNORM_INT8: VERIFIED <br/>
test histogram Successfull <br/>

## image_histogram.cpp <br/>
use real image file <br/>
calculate histogram  by GPU <br/>

### build sample code 
requires  <br/>
- macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>
- Devil <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/Devil <br/>


% g++ image_histogram.cpp  histogram_util.cpp devil_util.cpp parse_filename.cpp -o image_histogram -std=c++11 -framework OpenCL  `pkg-config --cflags --libs il`  <br/>

display following warning  <br/>
but don't mind <br/>
warning: 'clCreateImage2D' is deprecated:  <br/>

### run sample code 
Usage:  image_histogram   \<inputImageFile \> <br/>
ex ) <br/>
% ./image_histogram  ./images/baboon.jpg <br/>

### result 
display as below <br/>
Device Vendor: Intel Inc.  <br/>
save to: baboon_hist.txt  <br/>
image histogram Successfull  <br/>

read image file <br/>  
calculate histogram <br/> 
save to text file <br/> 

show graph  <br/>
created by python script <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-Histogram/result/baboon_hist_plot.png" width="300" /><br/>

### Docement
- https://qiita.com/ohwada/items/6435fdd34b1d8a52f6f8

### Reference 
- https://www.khronos.org/opencl/
- https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_14/histogram


OPenCL-Sobel
===============

OpenCL Sample <br/>
Sobel Edge Detection Filter <br/>


### build sample code 
requires  <br/>
- macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>
- FreeImage <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/FreeImage <br/>

% g++ sobel.cpp OpenCLFreeImageUtil.cpp freeimage_util.cpp  parse_filename.cpp -o sobel -std=c++11 -framework OpenCL -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage <br/>


display following warning  <br/>
but don't mind <br/>
warning: 'clCreateImage2D' is deprecated:  <br/>

### run sample code 
Usage:  sobel  \<inputImageFile \> [mode] <br/>
ex ) <br/>
% ./sobel  ./images/lena.jpg gray <br/>

### result 
read image file <br/>  
ex ) lena.jpg <br/>
and detect edge with SobelFilter <br/>
and write to output file  <br/>
 ex ) lena_gray_edge.png <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OPenCL-Sobel/result/lena_gray_edge.png" width="300" /><br/>

### Reference 
- https://www.khronos.org/opencl/
- http://www.heterogeneouscompute.org/?page_id=5


OpenCL-GaussianFilter
===============

OpenCL Sample <br/>
process Image with Gaussian Filter (Gaussian Blur)  <br/>
due to differences in Gaussian kernel parameters radius and sigma <br/>
Gaussian Blur is  smoothing an image with Gaussian Kernel <br/>

### build sample code 
requires  <br/>
- macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>
- FreeImage <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/FreeImage <br/>

% g++ GaussianFilter.cpp OpenCLFreeImageUtil.cpp freeimage_util.cpp parse_filename.cpp gaussian_kernel.cpp -o GaussianFilter -std=c++11 -framework OpenCL -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage <br/>

display following warning  <br/>
but don't mind <br/>
warning: 'clCreateImage2D' is deprecated:  <br/>

### run sample code 
Usage:  GaussianFilter  <inputImageFile> <radius> <sigma> <br/>
ex ) <br/>
% ./GaussianFilter  ./images/OpenCL_Logo.png 5 3.0 <br/>

### result 
read image file <br/>  
ex ) OpenCL_Logo.png <br/>
and convert Image with GaussianFilter <br/>
and write to output file  <br/>
 ex ) OpenCL_Logo_11x11_3.0_.png <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-GaussianFilter/result/OpenCL_Logo_11x11_3.0_.png" width="300" /><br/>

### Reference 
- https://www.khronos.org/opencl/
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCL-ImageFilter2D
- https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel


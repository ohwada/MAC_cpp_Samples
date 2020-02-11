OpenCL-ImageFilter2D
===============

OpenCL Sample <br/>

ImageFilter2D <br/>
this sample demonstrates performing Gaussian Filter (Gaussian Blur) on a 2D image using <br/>
Gaussian Blur is  smoothing an image with Gaussian Kernel <br/>


### build sample code 
requires:  <br/>
- macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>
- FreeImage <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/FreeImage <br/>

% g++ ImageFilter2D.cpp OpenCLUtil.cpp parse_filename.cpp  -o ImageFilter2D -std=c++11 -framework OpenCL -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage <br/>

display following warning  <br/>
but don't mind <br/>
warning: 'clCreateImage2D' is deprecated:  <br/>

Note: <br/>
Apple Announces that OpenGL and OpenCL will be Deprecated in macOS 10.14 Mojave <br/>
https://www.geeks3d.com/20180605/apple-announces-that-opengl-and-opencl-will-be-deprecated-in-macos-10-14-mojave/ <br/>


### run sample code 
Usage:   ImageFilter2D  <inputImageFile> [kernel size] <br/>
kernel size : 3(default) or 5 <br/>
when 3 use 3 x 3 Gaussian Kernel <br/>
 | 1 |  2 | 1 | <br/>
 | 2 | 4 | 2 | <br/>
 | 1 |  2 | 1 | <br/>
<br/>
when 5 use 5 x 5 Gaussian Kernel <br/>
 | 1 |  4 |   7 |   4 | 1 | <br/>
 | 4 | 16 | 26 | 16 | 4 | <br/>
 | 7 | 26 | 41 | 26 | 7 | <br/> 
 | 4 | 16 | 26 | 16 | 4 | <br/>
 | 1 |  4 |   7 |   4 | 1 | <br/>
<br/>
ex ) <br/>
% ./ImageFilter2D  ./images/rectangles.png 5 <br/>

### result 
read image file <br/>  
ex ) rectangles.png <br/>
and convert Image with GaussianFilter <br/>
and write to output file  <br/>
 ex ) rectangles_5x5.png <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-ImageFilter2D/result/rectangles_5x5.png" width="300" /><br/>


### Docement
- https://qiita.com/ohwada/items/34ca5175ad5aa146d680

### Reference 
- https://www.khronos.org/opencl/
- https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_8/ImageFilter2D
- https://en.wikipedia.org/wiki/Gaussian_filter
- https://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm


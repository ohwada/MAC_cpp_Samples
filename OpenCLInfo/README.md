OpenCLInfo
===============

OpenCL Sample <br/>

show OpenCL version and others <br/>


### whether MAC supports OpenCL
check with clinfo command <br/>
% brew install clinfo <br/>
% clinfo <br/>
display as below if suport <br/>
Platform Name Apple <br/>
Platform Version OpenCL 1.2 <br/>

### build and run sample code 
require:  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>

%g++ OpenCLInfo.cpp -std=c++11 -framework OpenCL  <br/>
% ./a.out <br/>

### result 
display as below <br/>
CL_PLATFORM_VENDOR:	Apple <br/>
CL_PLATFORM_VERSION:	OpenCL 1.2 <br/>
CL_DEVICE_NAME:	Intel(R) Core(TM) i7-5650U CPU @ 2.20GHz  <br/>
CL_DEVICE_VERSION:	OpenCL 1.2  <br/>

### Reference <br/>
- https://www.khronos.org/opencl/




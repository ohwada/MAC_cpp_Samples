OPenCL-HPPーVectorAdd
===============

OpenCL Sample <br/>
OpenCL C++ Wrapper API <br/>
this simple demonstrates use OpenCL C++ Wrapper API <br/>

### build sample code 
% g++ vecadd.cpp  -o vecadd -std=c++11 -framework opencl -I./include <br/>

display following warning  <br/>
but don't mind <br/>
warning: This version of the OpenCL Host API C++ bindings is deprecated <br/>
please use cl2.hpp instead  <br/>

### run sample code 
% ./vecadd

### result 
display as below <br/>
OpenCL C++ Bindings: vecaadd <br/>
Platform Name: Apple <br/>
Platform Version: OpenCL 1.2 <br/>
Device Name: Intel(R) Iris(TM) Graphics 6100 <br/>
Device Version: OpenCL 1.2  <br/>

### Reference <br/>
- https://www.khronos.org/opencl/
- https://github.khronos.org/OpenCL-CLHPP/
- https://github.com/bgaster/opencl-book-samples/tree/master/src/Chapter_12/VectorAdd


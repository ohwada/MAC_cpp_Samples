OpenCL-HelloWorld
===============

OpenCL Sample <br/>

operate simple addition with OpenCL<br/>
and display the result <br/>

### build and run sample code
requires:  <br/>
-  macOS  OpenCL framework <br/>
https://developer.apple.com/opencl/ <br/>
 - macOS  Xcode <br/>
https://developer.apple.com/jp/support/xcode/ <br/>

% g++ HelloWorld.cpp -o helloworld -std=c++11 -framework opencl <br/>
% ./HelloWorld <br/>  


### result 
display as below <br/>

HelloWorld <br/>
Platform Name:Apple <br/>
Device Name:Intel(R) Iris(TM) Graphics 6100 <br/>
 result  <br/>
0 3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57 60  <br/>


### Reference <br/>
- https://www.khronos.org/opencl/




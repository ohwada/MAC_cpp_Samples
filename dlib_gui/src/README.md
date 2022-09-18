dlib_gui: src
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/dlib_gui/screenshots/face_detect.png" width="300" /> <br/>


Reqire:
- x11
- libpng
- libjpeg

### sample 
- face_detect.cpp
- face_landmark_detect.cpp
- gui_api_ex.cpp


Build and run:  
% make face   
% bin/face   
> processing image images/lena.png
> Number of faces detected: 1


TODO:
eror when run gui_api_ex.cpp
> gui(25626,0x11e870dc0) malloc: *** error for object 0x7fc360507e10: pointer being freed was not allocated

dlib: src
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/dlib/screenshots/face_detect.png" width="300" /> <br/>


dlib has two types of face detector

(1) frontal_face_detector 
http://dlib.net/dlib/image_processing/frontal_face_detector.h.html

(2) dnn_mmod_face_detector
http://dlib.net/dnn_mmod_face_detection_ex.cpp.html

Reqire:
dnn model

### Note:
GUI feature is not available
because dfine DLIB_NO_GUI_SUPPORT
use OpenCV instead
try dlib_gui  


### sample 
- face_detect_frontal.cpp
- face_detect_dnn_mmod.cpp

Build and run:  
% make frontal   
% bin/frontal    
> saved: lena_out.png  


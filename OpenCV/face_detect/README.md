OpenCV: face_detect
===============


<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCV/screenshots/face_detect_cascade.png" width="300" />  

### overview
OpenCV has two types of image recognition futures

(1) Cascade Classifier
https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html


(2) DNN( Deep Neural Network )
(since 4.5.4)  
https://docs.opencv.org/4.x/d2/d58/tutorial_table_of_content_dnn.html

Deep Leaning
https://en.wikipedia.org/wiki/Deep_learning  

Preparation:
Download DNN Modeles  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenCV/setup  


### samples
- face_detect_cascade.cpp
- face_detect_dnn.cpp
- face_detect_dnn_video.cpp


Build and Run  
% make cascade  

% cd bin
 % ./cascade  
> created: lena_out.png

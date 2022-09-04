### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4` 

TARGET1=cascade
SRCS1=face_detect_cascade.cpp
TARGET2=dnn
SRCS2=face_detect_dnn.cpp
TARGET3=video
SRCS3=face_detect_dnn_video.cpp


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

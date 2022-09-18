## 2022-06-01 K.OHWADA


CXX=g++
CFLAGS=-Wall -std=c++11
DLIB_FLAGS=`pkg-config --cflags --libs dlib-1`
OCV_FLAGS=`pkg-config --cflags --libs opencv4`
TARGET1=frontal
SRCS1=face_detect_frontal.cpp
TARGET2=dnn
SRCS2=face_detect_dnn_mmod.cpp
TARGET3=landmark
SRCS3=face_detect_landmark.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(DLIB_FLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(DLIB_FLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(DLIB_FLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o


## 2022-06-01 K.OHWADA


CXX=g++
CFLAGS=-Wall -std=c++14
DLIB_FLAGS=`pkg-config --cflags --libs dlib_gui`


TARGET1=face
SRCS1=face_detect.cpp
TARGET2=landmark
SRCS2=face_landmark_detect.cpp
TARGET3=gui
SRCS3=gui_api_ex.cpp /usr/local/opt/dlib_gui/include/dlib/all/source.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $(SRCS1) $(CFLAGS) $(DLIB_FLAGS) -o bin/$@
	

$(TARGET2): $(SRCS2)
	$(CXX)  $(SRCS2) $(CFLAGS) $(DLIB_FLAGS)  -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX)  $(SRCS3) $(CFLAGS) $(DLIB_FLAGS)  -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o


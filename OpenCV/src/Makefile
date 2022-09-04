### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4`
TARGET1=image
SRCS1=image_show.cpp
TARGET2=video
SRCS2=video_show.cpp
TARGET3=capture
SRCS3=video_capture.cpp
TARGET4=version
SRCS4=version.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2): $(SRCS2)
	$(CXX) $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R videos bin


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(OCV_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) $(OCV_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o 

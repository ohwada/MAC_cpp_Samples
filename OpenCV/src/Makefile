### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4`
TARGET1=image
SRCS1=image_show.cpp
TARGET2=video
SRCS2=video_show.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(CFLAGS) $(OCV_FLAGS) -o $@


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) $(OCV_FLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o 

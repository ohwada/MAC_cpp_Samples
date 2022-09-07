### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4`

TARGET1=line
SRCS1=line.cpp
TARGET2=rectangle
SRCS2=rectangle.cpp
TARGET3=ellipse
SRCS3=ellipse.cpp
TARGET4=polylines
SRCS4=polylines.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(OCV_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) $(OCV_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o 

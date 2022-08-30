### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
WRITER_FLAGS=`pkg-config --cflags --libs pngwriter`
TARGET=sin
SRCS=sin.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(WRITER_FLAGS)  -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/sin*  bin/lib/*  *.o 

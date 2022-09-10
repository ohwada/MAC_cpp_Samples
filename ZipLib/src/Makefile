### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ZIPLIB_FLAGS=`pkg-config --cflags --libs ziplib`
TARGET=show
SRCS=show_zip.cpp


$(TARGET): $(SRCS)
	$(CXX)  $< $(CFLAGS) $(ZIPLIB_FLAGS) -o bin/$@ 


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o


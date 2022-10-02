### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ZIP_FLAGS=`pkg-config --cflags --libs libzippp`

TARGET=show
SRCS=show_zip.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(ZIP_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

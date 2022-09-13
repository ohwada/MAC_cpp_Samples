### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
LZMA_FLAGS=`pkg-config --cflags --libs liblzma`

TARGET=encoder
SRCS=encoder.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(LZMA_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

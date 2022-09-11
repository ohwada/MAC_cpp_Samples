### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++17
UUID_FLAGS=`pkg-config --cflags stduuid` 
MAC_FLAGS=-framework CoreFoundation 
TARGET=gen
SRCS=gen_uuid.cpp


$(TARGET): $(SRCS)
	$(CXX)  $< $(CFLAGS) $(UUID_FLAGS) $(MAC_FLAGS) -o bin/$@ 



%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o


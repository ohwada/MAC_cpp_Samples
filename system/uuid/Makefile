### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MAC_FLAGS=-framework CoreFoundation
TARGET=cfuuid
SRCS=cfuuid.cpp


$(TARGET): $(SRCS)
	$(CXX)  $< $(CFLAGS) $(MAC_FLAGS) -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o


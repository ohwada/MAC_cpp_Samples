### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
PUGI_FLAGS=`pkg-config --cflags --libs  pugixml` 
TARGET=movie2
SRCS=movie2.cpp
 

$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(PUGI_FLAGS) -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o


### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
 FMT_FLAGS=`pkg-config --cflags --libs fmt`

TARGET=chrono
SRCS=chrono.cpp


$(TARGET):  $(SRCS)
	$(CXX)  $<  $(CFLAGS)  $(FMT_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

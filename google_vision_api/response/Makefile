### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4`

TARGET=show
SRCS=show_response.cpp


$(TARGET):  $(SRCS)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

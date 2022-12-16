### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`  

TARGET=server
SRCS=websocket.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags  boost`
TARGET=server
SRCS=simple_http_server.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
WEBSOCKET_FLAGS=`pkg-config --cflags websocketpp`
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET1=server
SRCS1=echo_server.cpp
TARGET2=client
SRCS2=echo_client.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(WEBSOCKET_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(WEBSOCKET) $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

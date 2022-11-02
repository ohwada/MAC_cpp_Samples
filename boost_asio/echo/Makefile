### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++03
BOOST_FLAGS=`pkg-config --cflags --libs  boost`

TARGET1=server
SRCS1=blocking_tcp_echo_server.cpp
TARGET2=client
SRCS2=blocking_tcp_echo_client.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

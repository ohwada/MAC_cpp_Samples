### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++03
BOOST_FLAGS=`pkg-config --cflags --libs  asio`

TARGET1=server
SRCS1=udp_echo_server.cpp
TARGET2=client
SRCS2=udp_echo_client.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

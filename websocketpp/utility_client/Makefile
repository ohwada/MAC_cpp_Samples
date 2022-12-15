### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
WSPP_FLAGS=`pkg-config --cflags  websocketpp`
ASIO_FLAGS=`pkg-config --cflags --libs  asio`


TARGET=client
SRCS=utility_client.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(WSPP_FLAGS) $(ASIO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*   *.o 

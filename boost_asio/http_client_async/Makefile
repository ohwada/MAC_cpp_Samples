### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++03
BOOST_FLAGS=`pkg-config --cflags boost`


TARGET=client
SRCS=http_client_async.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

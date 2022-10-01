### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
SOCKPP_FLAGS=`pkg-config --cflags --libs sockpp`
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET=client
SRCS=client.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(SOCKPP_FLAGS) $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

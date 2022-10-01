### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
SOCKPP_FLAGS=`pkg-config --cflags --libs sockpp`

TARGET1=server
SRCS1=server.cpp
TARGET2=client
SRCS2=client.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(SOCKPP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(SOCKPP_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

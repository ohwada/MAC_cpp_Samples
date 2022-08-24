### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

 CURLCPP_FLAGS=`pkg-config --cflags --libs curlcpp` 
TARGET=client
SRCS=http_client.cpp


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(CURLCPP_FLAGS)  $(LIBCURL_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

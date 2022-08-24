### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

 CURLCPP_FLAGS=`pkg-config --cflags --libs curlcpp` 
 JSON_FLAGS=`pkg-config --cflags --libs jsoncpp`

TARGET=imap
SRCS=imap.cpp


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(CURLCPP_FLAGS) $(JSON_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

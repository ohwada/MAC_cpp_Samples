### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags boost`


TARGET1=hello
SRCS1=http_hello_server_async.cpp
TARGET2=file
SRCS2=http_file_server_async.cpp
TARGET3=test
SRCS3= test_request_parser.cpp



$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

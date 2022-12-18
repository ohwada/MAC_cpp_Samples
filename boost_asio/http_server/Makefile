### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++03
BOOST_FLAGS=`pkg-config --cflags  boost`

HTTP_SRCS=server.cpp connection.cpp connection_manager.cpp mime_types.cpp reply.cpp request_handler.cpp request_parser.cpp

TARGET1=hello
SRCS1=http_hello_server.cpp $(HTTP_SRCS)
TARGET2=index
SRCS2=http_index_server.cpp $(HTTP_SRCS)
TARGET3=file
SRCS3=http_file_server.cpp $(HTTP_SRCS)


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

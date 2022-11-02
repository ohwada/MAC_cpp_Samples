### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++03
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET=server
SRCS=main.cpp server.cpp connection.cpp connection_manager.cpp mime_types.cpp reply.cpp request_handler.cpp request_parser.cpp


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

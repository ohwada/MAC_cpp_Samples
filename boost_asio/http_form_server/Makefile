### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET1=server
SRCS1=main.cpp server.cpp connection.cpp connection_manager.cpp mime_types.cpp reply.cpp request_handler.cpp request_parser.cpp
TARGET2=test
SRCS2=test_form.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp1
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

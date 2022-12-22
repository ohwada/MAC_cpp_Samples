### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
# BOOST_FLAGS=`pkg-config --cflags  boost`
BEAST_FLAGS=-I./include

TARGET=server
SRCS=chat_multi.cpp  http_session.cpp listener.cpp   shared_state.cpp websocket_session.cpp


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(BEAST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*   *.o 

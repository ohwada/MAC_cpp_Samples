### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
WSPP_FLAGS=`pkg-config --cflags  websocketpp`
ASIO_FLAGS=`pkg-config --cflags --libs  asio`


TARGET1=step1
SRCS1=step1.cpp
TARGET2=step2
SRCS2=step2.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(WSPP_FLAGS) $(ASIO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(WSPP_FLAGS) $(ASIO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*   *.o 

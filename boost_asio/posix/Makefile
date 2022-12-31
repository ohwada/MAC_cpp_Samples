### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS11=-Wall -std=c++11
CFLAGS14=-Wall -std=c++14
BOOST_FLAGS=`pkg-config --cflags --libs boost`

TARGET1=stream1
SRCS1=posix_stream_descriptor1.cpp
TARGET2=stream2
SRCS2=posix_stream_descriptor2.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS11) $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS14) $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

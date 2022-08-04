### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
BOOST_URL_INC=-I/usr/local/include/boost_url
TARGET=parse
SRCS=parse_uri.cpp


$(TARGET): $(SRCS)
	$(CXX) $(CFLAGS) $(BOOST_URL_INC) $< -o $@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o


### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
HTTPXX_FLAGS=`pkg-config --cflags --libs httpxx`
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET=server
SRCS=httpd_file_browser.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(HTTPXX_FLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

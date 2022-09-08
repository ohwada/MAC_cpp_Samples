### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
 CURL_FLAGS=`pkg-config --cflags --libs curlpp`


TARGET=send
SRCS=send_request.cpp


$(TARGET):  $(SRCS)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@
	cp -R data bin


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

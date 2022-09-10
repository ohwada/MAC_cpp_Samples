### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
 CURL_FLAGS=`pkg-config --cflags --libs curlpp`


TARGET1=client
SRCS1=http_client.cpp
TARGET2=form
SRCS2=http_post_form_to_memory.cpp
TARGET3=json
SRCS3=http_post_json_to_memory.cpp

$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

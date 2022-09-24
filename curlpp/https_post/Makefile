### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
 CURL_FLAGS=`pkg-config --cflags --libs curlpp`

TARGET1=form_memory
SRCS1=https_post_form_to_memory.cpp
TARGET2=json_memory
SRCS2=https_post_json_to_memory.cpp
TARGET3=form_file
SRCS3=https_post_form_to_file.cpp
TARGET4=json_file
SRCS4=https_post_json_to_file.cpp

$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


$(TARGET4):  $(SRCS4)
	$(CXX)  $<  $(CFLAGS)  $(CURL_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

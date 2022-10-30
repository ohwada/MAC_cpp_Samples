### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON
CURL_FLAGS=`pkg-config --cflags --libs curlpp`
 JSON_FLAGS=`pkg-config --cflags --libs jsoncpp`


TARGET1=server
SRCS1=local_server.cpp
TARGET2=access
SRCS2=request_access_token.cpp
TARGET3=send
SRCS3=send_mail_text.cpp


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS)  $(POCO_FLAGS) $(CURL_FLAGS)   $(JSON_FLAGS)  -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS)   $(CURL_FLAGS) $(POCO_FLAGS) $(JSON_FLAGS) -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS)  $(POCO_FLAGS) $(CURL_FLAGS)   $(JSON_FLAGS)  -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* log/* *.o 

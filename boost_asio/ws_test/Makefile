### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags boost`

TARGET1=frame
SRCS1=test_ws_frame_parser.cpp
TARGET2=key
 SRCS2=test_gen_accept_key.cpp
TARGET3=request
 SRCS3=test_ws_request_parser.cpp 
TARGET4=response
 SRCS4=test_ws_response_parser.cpp 
TARGET5=server
 SRCS5=test_ws_server_frame_builder.cpp
TARGET6=client
 SRCS6=test_ws_client_frame_builder.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET6): $(SRCS6)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 

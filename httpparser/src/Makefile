### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

PARSER_FLAGS=`pkg-config --cflags httpparser` 
TARGET1=request
SRCS1=parse_request.cpp
TARGET2=response
SRCS2=parse_response.cpp
TARGET3=url
SRCS3=parse_url.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $< $(CFLAGS)  $(PARSER_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX)  $< $(CFLAGS)  $(PARSER_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX)  $< $(CFLAGS)  $(PARSER_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

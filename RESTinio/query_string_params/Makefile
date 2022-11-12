### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`  

TARGET=query
SRCS=query_string_params.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

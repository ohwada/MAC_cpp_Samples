### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`  
CLARA_FLAGS=`pkg-config --cflags --libs clara` 

TARGET1=hello
SRCS1=hello_world_sendfile.cpp
TARGET2=sendfiles
SRCS2=sendfiles.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) $(CLARA_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) $(CLARA_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

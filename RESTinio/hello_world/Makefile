### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`  

TARGET1=minimal
SRCS1=hello_world_minimal.cpp
TARGET2=basic
SRCS2=hello_world_basic.cpp
TARGET3=hello
SRCS3=hello_world.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 

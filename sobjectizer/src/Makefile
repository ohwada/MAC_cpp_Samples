### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++17
SO_FLAGS=`pkg-config --cflags --libs  sobjectizer`

TARGET=hello
SRCS=hello_world.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(SO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

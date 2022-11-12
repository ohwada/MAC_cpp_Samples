### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
 CLARA_FLAGS=`pkg-config --cflags clara`

TARGET=parse
SRCS=parse_width.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(CLARA_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
